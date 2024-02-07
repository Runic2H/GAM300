#version 450
layout(location = 0) in vec3 vPosition;

layout(location = 0) out vec3 fragColor;




struct DebugInstance
 {
	mat4 TransformMatrix;
	vec4 DebugColor;
};

layout (binding = 5) uniform FontUBO 
{
    mat4 Proj;
    mat4 View;
}ubo;


layout(std140, binding = 15) readonly buffer ShaderDataBuffer
{
    DebugInstance Instances[];
};

layout (push_constant) uniform Push
{
    uint offset;
}push;


void main()
{
    const DebugInstance instanceCurr = Instances[push.offset + gl_InstanceIndex];
    mat4 xform = instanceCurr.TransformMatrix;
    fragColor = vec3(0.f, 1.f, 0.f);
    gl_Position = ubo.Proj * ubo.View * xform * vec4(vPosition,1.0);
}