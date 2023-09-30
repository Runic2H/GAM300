#version 450

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec4 vNormals;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;


// layout(binding = 0) uniform UniformBufferObject
// {
//     mat4 model;
//     mat4 view;
//     mat4 proj;
// }ubo;

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
    vec3 position_in_world = (push.modelMatrix * vec4(vPosition, 1.0)).xyz;
    gl_Position = PL.proj * PL.view *push.modelMatrix* vec4(vPosition, 1.0);
    
    vec3 normalworldspace = normalize(mat3(push.normalMatrix) * vNormals.xyz);
    vec3 directiontolight = PL.pointlights[0].Position.xyz - position_in_world;
    vec3 lightcolor  = PL.pointlights[0].Color.xyz * PL.pointlights[0].Color.w;
    vec3 ambientlight = PL.ambientlightcolor.xyz * PL.ambientlightcolor.w;
    vec3 diffuselight = lightcolor* max(dot(normalworldspace, normalize(directiontolight)),0);

    fragColor =  (diffuselight + ambientlight)*vColor;
    fragTexCoord = inTexCoord;
}