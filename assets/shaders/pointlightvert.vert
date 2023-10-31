#version 450

const vec2 OFFSET[6] = vec2[](
    vec2(-1.0, -1.0),
    vec2(1.0, -1.0), 
    vec2(-1.0, 1.0),
    vec2(1.0, -1.0), 
    vec2(1.0, 1.0),
    vec2(-1.0, 1.0)); 


layout (location = 0) out vec2 fragoffset;

struct PointLight {
    vec4 Position;
    vec4 Color;
    vec4 pad[2];
};

//for the scene
layout(set = 0, binding = 1) uniform GlobalUBO {
    mat4 proj;
    mat4 view;
    //mat4 InvView;
    vec4 ambientlightcolor;
    PointLight pointlights[10];
    int activelights;
    vec4 pad[15];
} ubo;

layout(push_constant) uniform Push {
    vec4 Pos;
    vec4 Color;
    float radius;
} push;

void main() {
    fragoffset = OFFSET[gl_VertexIndex];
    vec3 WorldCameraRight = {ubo.view[0][0], ubo.view[1][0], ubo.view[2][0]};
    vec3 WorldCameraUp = {ubo.view[0][1], ubo.view[1][1], ubo.view[2][1]};

    vec3 worldPos = push.Pos.xyz + 
    push.radius * fragoffset.x * WorldCameraRight+ 
    push.radius* fragoffset.y * WorldCameraUp;
    gl_Position = ubo.proj * ubo.view* vec4(worldPos, 1.0);
}
