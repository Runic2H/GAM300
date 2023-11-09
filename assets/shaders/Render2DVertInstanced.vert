#version 450

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 inTexCoord;
//layout(location = 2) in vec3 vColor;
//layout(location = 3) in vec4 vNormals;
struct UIInstance
{
    mat4 model;
    vec4 color;
    vec4 texID;
};

layout(std140, binding = 10) readonly buffer ShaderDataBuffer
{
    UIInstance instances[];
};


layout (std140, binding = 25) uniform ScreenInfo
{
	mat4 Projection;
    mat4 View;
    uint ViewingFrom2D;
    float padding[3];

} scene2D;

layout(push_constant) uniform Push 
{
    mat4 testmodel;
    uint dataOffset;
    float padding[3];
};


layout(location = 0) out vec4 outColor;
layout(location = 1) out vec3 outPosition;
layout(location = 2) out vec2 outTextureCoord;
layout(location = 3) out uint outTextureIndex;


void main()
{
	uint index = dataOffset + gl_InstanceIndex;
	mat4 model = instances[index].model;
    uint texID = uint(instances[index].texID.x);
    
    outColor = instances[index].color;
    outTextureIndex = texID;
    outPosition = (model * vec4(vPosition, 1.0)).xyz;
    outTextureCoord = inTexCoord;
    
    if (scene2D.ViewingFrom2D == 1)
    {
        gl_Position = scene2D.Projection * vec4(outPosition, 1.0);
    }
    else
    {
        gl_Position = scene2D.Projection * scene2D.View * vec4(outPosition, 1.0);
    }
}

