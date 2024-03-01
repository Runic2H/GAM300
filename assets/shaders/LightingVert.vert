#version 450

layout(location =0) in vec3 vPosition;
layout(location =1) in vec3 vColor;
layout(location =2) in vec2 inTexCoord;
layout(location =3) in vec4 vNormals;

layout(location =0) out vec3 fragColor;
layout(location =1) out vec2 fragTexCoord;
layout(location =2) out vec3 fragPosWorld;
layout(location =3) out vec3 fragNormalWorld;
layout(location =4) out flat uint id;
layout(location =5) out vec4 clipspacepos;

struct PointLight {
    vec4 Position;
    vec4 Color;
    vec4 pad[2];

    vec3 attenuation;// constant, linear quadratic stored in that order
};

struct DirectionalLight {
    vec3 direction;
    vec4 Color;
};

struct SpotLight {
    vec4 Position;
    vec3 direction;
    float cutoff;
    float outerCutoff;

    vec4 Color;
};

//global ubo
layout(set = 0, binding = 0) uniform GlobalUBO{
    mat4 proj; //camera
    mat4 view; //camera
    vec4 ambientlightcolor;// surrounding Color
    PointLight pointlights[50]; //
    DirectionalLight DirLight[10];
    SpotLight SptLight[10];
    int activepointlights;  
}PL;

//data from the model
layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
    uint textureIndex;
    float padding[3]; 
    uint id;
} push;

void main(){

    vec4 position_in_world = push.modelMatrix* vec4(vPosition,1.0);
    id = push.id;

    vec4 clipspacepos = PL.proj * PL.view* position_in_world;
    gl_Position = clipspacepos;

    fragNormalWorld = normalize(mat3(push.normalMatrix)* vNormals.xyz);
    fragPosWorld = position_in_world.xyz;

    fragColor = vColor;
    fragTexCoord = inTexCoord;
}