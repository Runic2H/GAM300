#version 450
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 0) out vec3 fragColor;

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
    PointLight pointlights[10];
    int activelights;
    vec4 pad[15];    
}PL;
layout(push_constant) uniform Push{
    mat4 TransformMatrix;
    vec4 DebugColor;
}push;
void main(){
    gl_Position = PL.proj * PL.view * push.TransformMatrix * vec4(vPosition,1.0);
    fragColor = push.DebugColor.xyz;
}