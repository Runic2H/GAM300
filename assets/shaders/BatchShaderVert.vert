#version 450

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vBiTangent;
layout(location = 2) in vec3 vTangent;
layout(location = 3) in vec3 vNormals;
layout(location = 4) in vec2 vUV;
layout(location = 5) in vec4 vColor;
layout(location = 6) in vec4 BoneIDs;
layout(location = 7) in vec4 Weights;
layout(location = 8) in vec2 meshID;


/*
struct PointLight{
    vec4 Position;
    vec4 Color;
    vec4 pad[2];
};
*/

layout(set = 0, binding = 5) uniform SceneUBO
{
    mat4 proj;
    mat4 view;  
}Scene3D;

struct BatchData
{
    mat4 modelMatrix;
    uint matID;
    uint textureID;
    uint isRender;
    uint entityID;
    uint m_AnimOffset;
    uint m_IsAnimated;
};


layout(std140, binding = 15) readonly buffer BatchBuffer
{   
	BatchData batch[];
};

// for phong bling bling
struct Material
{
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;

    float shininess;
    float reflectivity;
    float opacity;
    uint diffuseID;
    
    uint specularID;
    uint normalID;
    uint emissiveID;
    uint opacityID;
 
};



layout(location = 0) out vec4 fragColor;
layout(location = 1) out vec2 fragTexCoord;
layout(location = 2) out vec3 fragPosWorld;
layout(location = 3) out vec3 fragNormalWorld;
layout(location = 4) out flat uint id;
layout(location = 5) out vec4 clipspacepos;
layout(location = 6) out flat uint texID;
layout(location = 7) out float linearDepth;
layout(location = 8) out uint isRenderable;

void main() 
{

    
    BatchData batchData = batch[uint(meshID.x)];

    uint materialID = batchData.matID;
    uint textureID = batchData.textureID;
    mat4 modelMatrix = batchData.modelMatrix;

    mat4 skinMat = mat4(1.0);


    mat4 accumulated = modelMatrix * skinMat;
    
    vec4 position_in_world = accumulated * vec4(vPosition, 1.0);
    fragTexCoord = vUV;
    
    id = batchData.entityID;

    vec4 clipspacepos = Scene3D.proj * Scene3D.view * position_in_world;
    gl_Position = clipspacepos;
    
    vec3 normal = mat3(transpose(inverse(accumulated))) * vNormals;
    vec3 tangent = mat3(accumulated) * vTangent;
    vec3 bitangent = mat3(accumulated) * vBiTangent;
    mat3 TBN = mat3(tangent, bitangent, normal);
 
    fragNormalWorld = normal;
    fragPosWorld = position_in_world.xyz;
    texID = textureID;
    fragColor = vColor;
    linearDepth = -(Scene3D.view * position_in_world).z;
    
    isRenderable = batchData.isRender;
}