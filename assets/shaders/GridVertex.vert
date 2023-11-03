#version 450

layout(location = 0) in vec3 vPosition; 

struct GridUniform
{
    mat4 model;
    mat4 view;
    mat4 proj;
    vec4 gridColor;
};

layout(std140, binding = 27) readonly buffer GridUBO
{
    GridUniform gridInstance[];
} gridUBO;

layout(location = 0) out vec3 fColor;


void main() 
{
    GridUniform gridUniform = gridUBO.gridInstance[gl_InstanceIndex];
    gl_Position = gridUniform.proj * gridUniform.view * gridUniform.model * vec4(vPosition, 1.0);
    fColor = gridUniform.gridColor.xyz;

}