
#version 450


layout(set = 1, binding = 4) uniform sampler2D texArraySampler[1000];

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragPosWorld;
layout(location = 3) in vec3 fragNormalWorld; 
layout(location = 4) in flat uint id;
layout(location = 5) in vec4 clipspacepos;
layout(location = 6) flat in uint texID;
layout(location = 7) in float linearDepth;
layout(location = 8) flat in uint isRenderable;


layout (location = 0) out vec4 outColor;
layout (location = 1) out uint outID;
void main() 
{
    if (isRenderable == 0) discard;

    int textureID = int(texID);
    outID = id;
    outColor = texture(texArraySampler[textureID], fragTexCoord);

}