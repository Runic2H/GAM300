#version 450

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec4 vNormals;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragPosWorld;
layout(location = 3) out vec3 fragNormalWorld;

struct PointLight{
    vec4 Position;
    vec4 Color;
};

//for the scene
layout(set = 0, binding = 0) uniform GlobalUBO{
    mat4 proj;
    mat4 view;
    //mat4 InvView;
    vec4 ambientlightcolor;
    PointLight pointlights[10];    
}PL;

layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
} push;

void main(){
}
