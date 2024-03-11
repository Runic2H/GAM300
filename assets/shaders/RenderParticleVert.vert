#version 450 core

struct Particle {
    //transform params
    vec4 Size;
    vec4 Rotation;
    vec4 CurrentPosition;
    
    vec4 Velocity;
    vec4 Acceleration;
    vec4 Color;
    float Age;
    uint Active;
};

layout (std140, binding = 31) buffer Particles {
    Particle List[];
}v_Particles;

layout (std140 ,binding = 5) buffer Camera{
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
}Cam;

layout (std140, binding = 34) buffer TransformMatrix{
    mat4 List[];
}v_TransformMatrix;

//vertex positions
layout (location = 0) in vec3 in_Position;

//output to fragment shader
layout (location = 0) out vec3 out_Color;

void main(){
    int index = gl_InstanceIndex;

    mat4 currentParticlexform = v_TransformMatrix.List[index];

    //transform the vertex position
    vec4 worldPosition = currentParticlexform * vec4(in_Position, 1.0);
    gl_Position = Cam.ProjectionMatrix * Cam.ViewMatrix * worldPosition;

    //output the color
    out_Color = v_Particles.List[index].Color.rgb;

    //if the particle is not active, don't draw it
    if(v_Particles.List[index].Active == 0){
        gl_Position = vec4(0.0, 0.0, 0.0, 0.0);
    }
}