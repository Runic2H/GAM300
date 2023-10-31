#version 450

layout(location = 0) in vec3 vPosition; 
layout(location = 1) out vec2 outTexCoord;

struct Instance
{
    vec2 m_StartUV; 
    vec2 m_EndUV; 
    mat4 model;
};

layout(std140, binding = 1) readonly buffer InstanceBuffer 
{
    Instance instances[];
} instanceData;

layout (binding = 2) uniform FontUBO 
{
	mat4 projection;
    mat4 view;
} ubo;



void main() 
{
    uint index = gl_InstanceIndex;
    mat4 model = instanceData.instances[index].model;
    vec2 deltaUV = instanceData.instances[index].m_EndUV - instanceData.instances[index].m_StartUV;
    outTexCoord.x = vPosition.x < 0.0 ? instanceData.instances[index].m_StartUV.x : instanceData.instances[index].m_StartUV.x + deltaUV.x;
    outTexCoord.y = vPosition.y < 0.0 ? instanceData.instances[index].m_StartUV.y : instanceData.instances[index].m_StartUV.y + deltaUV.y;
    gl_Position = ubo.projection * ubo.view * model * vec4(vPosition, 5.0);
}
