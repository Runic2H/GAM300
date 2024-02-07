#version 450

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec4 vNormals;


layout (std140, binding = 25) uniform ScreenInfo
{
	mat4 Projection;
    mat4 View;
    uint ViewingFrom2D;
    float padding[3];

} scene2D;

layout(push_constant) uniform Push 
{
    mat4 pushmodel;
    vec4 pushtexID;

}pushData;


layout(location = 0) out vec4 outColor;
layout(location = 1) out vec3 outPosition;
layout(location = 2) out vec4 outNormal;
layout(location = 3) out vec2 outTextureCoord;
layout(location = 4) out uint outTextureIndex;

void main()
{
	mat4 model = pushData.pushmodel;
    uint texID = uint(pushData.pushtexID.x);
    
    outColor = vec4(vColor, 1.f);
    
    outTextureIndex = texID;
    outPosition = vec3(model * vec4(vPosition, 1.0));
    outNormal = mat4(model) * vNormals;
    outTextureCoord = inTexCoord;
    
    if (scene2D.ViewingFrom2D == 1)
    {
        gl_Position = scene2D.Projection * vec4(outPosition, 1.0);
    }
    else
    {
        gl_Position = scene2D.Projection * scene2D.View * vec4(outPosition, 1.0);
    }
}

