#version 450

layout(location = 0) in vec3 vPosition;

struct GridUniform
{
    mat4 model;
    mat4 view;
    mat4 proj;
};

layout(std140, binding = 30) readonly buffer GridLineUBO
{
    GridUniform gridInstance[];
} gridLineUBO;

void main() 
{
    GridUniform gridUniform = gridLineUBO.gridInstance[gl_InstanceIndex];
    gl_Position = gridUniform.proj * gridUniform.view * gridUniform.model * vec4(vPosition, 1.0);
}
