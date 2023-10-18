
#version 450

layout(location = 0) in vec3 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragPosWorld;
layout(location = 3) in vec3 fragNormalWorld;  

layout(location = 0) out vec4 outColor;

struct PointLight{
    vec4 Position;
    vec4 Color;
};

layout(set = 0, binding = 0) uniform GlobalUBO{
    mat4 proj;
    mat4 view;
    //mat4 InvView;
    vec4 ambientlightcolor;
    PointLight pointlights[10];    
}PL;

//updated per frame per model
layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

void main() {
}