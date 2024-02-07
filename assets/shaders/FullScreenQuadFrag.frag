#version 450
layout(location = 0) in vec2 inTexCoord;   

layout(binding = 12) uniform sampler2D screenTexture;

layout(location = 0) out vec4 outColor;

void main()
{
    outColor = texture(screenTexture, inTexCoord);
}
