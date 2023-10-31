#version 450

layout(location = 1) in vec2 inTexCoords;
layout(location = 3) out vec4 outColor;

layout(binding = 3) uniform sampler2D msdf;

layout(binding = 4) uniform FontColors {
    vec4 bgColor;
    vec4 fgColor;
    float pxRange;
} fontColors;

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

vec4 linearToGamma(vec4 linearColor) {
    bvec4 condition = lessThanEqual(linearColor, vec4(0.0031308));
    vec4 linearPortion = linearColor * 12.92;
    vec4 gammaPortion = pow(linearColor, vec4(1.0/2.4)) * 1.055 - 0.055;
    return mix(gammaPortion, linearPortion, vec4(condition));
}

float screenPxRange() {
    vec2 unitRange = vec2(fontColors.pxRange)/vec2(textureSize(msdf, 0));
    vec2 screenTexSize = vec2(1.0)/fwidth(inTexCoords);
    return max(0.5*dot(unitRange, screenTexSize), 1.0);
}

void main() {
    vec3 msd = texture(msdf, inTexCoords).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);

    vec4 gammaBgColor = linearToGamma(fontColors.bgColor);
    vec4 gammaFgColor = linearToGamma(fontColors.fgColor);
    //Set out color to red to test if the shader is working
    outColor = vec4(1.0, 0.0, 0.0, 1.0);
}
