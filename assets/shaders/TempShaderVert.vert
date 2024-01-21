#version 450

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vBiTangent;
layout(location = 2) in vec3 vTangent;
layout(location = 3) in vec3 vNormals;
layout(location = 4) in vec2 vUV;
layout(location = 5) in vec4 vColor;
layout(location = 6) in vec4 BoneIDs;
layout(location = 7) in vec4 Weights;

layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragPosWorld;
layout(location = 3) out vec3 fragNormalWorld;
layout(location = 4) out flat uint id;
layout(location = 5) out vec4 clipspacepos;

struct PointLight{
    vec4 Position;
    vec4 Color;
    vec4 pad[2];
};

//for the scene
layout(set = 0, binding = 0) uniform GlobalUBO{
    mat4 proj;
    mat4 view;
    //mat4 InvView;
    vec4 ambientlightcolor;
    PointLight pointlights[50];
    int activelights;
    vec4 pad[15];    
}PL;



//updated per frame per model
layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
    uint textureIndex;
    float padding[3]; 
    uint id;
} push;




void main() 
{
    vec4 position_in_world = push.modelMatrix * vec4(vPosition, 1.0);

    id = push.id;
    
    vec4 clipspacepos = PL.proj * PL.view * position_in_world;
    gl_Position = clipspacepos;
    
    fragNormalWorld = normalize(mat3(push.normalMatrix) * vNormals);
    fragPosWorld = position_in_world.xyz;

    fragColor = vColor;
    fragTexCoord = vUV;
}