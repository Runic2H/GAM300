#version 450

layout(location = 0) in vec3 vPosition;

struct Instance
{
    mat4 model;
    vec4 color;
    vec4 bgColor;
    vec4 fgColor;
    vec4 startendUV;
    vec4 texID;
};

layout(std140, binding = 10) readonly buffer InstanceBuffer 
{
    Instance instances[];
} instanceData;

layout (binding = 25) uniform FontUBO 
{
	mat4 projection;
    mat4 view;
    uint ViewingFrom2D;
    float padding[3];
} ubo;

layout(push_constant) uniform Push 
{
    uint offset;
};
layout(location = 0) out vec3 outPosition;
layout(location = 1) out vec4 outColor;
layout(location = 2) out vec2 outTexCoord;
layout(location = 3) out vec4 outBGColor;
layout(location = 4) out vec4 outFGColor;
layout(location = 5) out vec2 outTextureCoord;
layout(location = 6) out float OutPxRange;
layout(location = 7) out uint outTextureIndex;

void main() 
{
    uint index = offset + gl_InstanceIndex;
    mat4 model = instanceData.instances[index].model;

    vec2 startUV = instanceData.instances[index].startendUV.xy;
    vec2 endUV = instanceData.instances[index].startendUV.zw;

    vec2 deltaUV = endUV - startUV;
    vec2 normalizedPosition = vPosition.xy + 0.5;

    outTexCoord = mix(startUV, endUV, normalizedPosition);
    
    outColor = instanceData.instances[index].color;
    outBGColor = instanceData.instances[index].bgColor;
    outFGColor = instanceData.instances[index].fgColor;
    outTextureIndex = uint(instanceData.instances[index].texID.x);
    outPosition = (model * vec4(vPosition, 1.0)).xyz;
    OutPxRange = ubo.padding[0];
    if (ubo.ViewingFrom2D == 1)
    {
        gl_Position = ubo.projection * vec4(outPosition, 1.0);
    }
    else
    {
        gl_Position = ubo.projection * ubo.view * vec4(outPosition, 1.0);
    }
}
