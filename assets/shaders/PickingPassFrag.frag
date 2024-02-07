
#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragPosWorld;
layout(location = 3) in vec3 fragNormalWorld;  

layout(location = 0) out uint outColor;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
    uint entityID;
    float padding[3]; 
} pushConst;

void main() 
{
    outColor = pushConst.entityID;

}