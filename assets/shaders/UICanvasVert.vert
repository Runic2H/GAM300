#version 450

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 inTexCoord;



layout(set = 0, binding = 2) uniform UBO
{
    mat4 proj;
    mat4 view;   
}UniformBuffer;



//updated per frame per model
layout(push_constant) uniform Push
{
    mat4 modelMatrix;
} push;

layout(location = 0) out vec2 fragTexCoord;


void main() 
{
    vec4 position_in_world = push.modelMatrix * vec4(vPosition, 1.0);
    gl_Position = UniformBuffer.proj * UniformBuffer.view * push.modelMatrix* vec4(vPosition, 1.0);
    
    fragTexCoord = inTexCoord;
}