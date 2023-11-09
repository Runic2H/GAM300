
#version 450

layout(binding = 3) uniform sampler2D outputSampler;

layout(location = 0) in vec2 fragTexCoord;
layout(location = 0) out vec4 outColor;

void main() 
{
    vec4 texColor = texture(outputSampler, fragTexCoord);
    outColor = texColor;
}