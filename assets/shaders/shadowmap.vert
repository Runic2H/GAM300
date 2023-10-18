#version 450

#extension GL_ARB_shading_language_420pack : enable

layout(set = 0, binding = 0) uniform vp_ubo{
    mat4 Viewprojection;
}VP;

layout(set = 0 , binding =1) uniform m_ubo{
    mat4 Model[16];
}M;

layout(location =0) in vec3 vPos;

void main(){
    vec4 pos = vec4(vPos.x, vPos.y, vPos.z,1.0);
    vec4 worldpos = M.Model[gl_InstanceIndex] * pos;
    gl_Position = VP.Viewprojection *worldpos;
}