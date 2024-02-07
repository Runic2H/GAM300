#version 450

layout (location = 0) in vec3 inPos;

layout (binding = 2) uniform SKYBOXUBO
{
    mat4 projection;
    mat4 view;
} skyubo;

layout (location = 0) out vec3 outskyUV;
void main()
{
    outskyUV = inPos;
    //Convert cubemap into coordinate space
    //outskyUV.y *= -1.0;
    //outskyUV.x *= -1.0;
    outskyUV.z *= -1.0;
    gl_Position = skyubo.projection * skyubo.view * vec4(inPos.xyz, 1.0);
}