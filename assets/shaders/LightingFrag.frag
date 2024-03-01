#version 450

layout(set = 1, binding = 4) uniform sampler2D texArraySampler[500];

layout(location =0) in vec3 fragColor;
layout(location =1) in vec2 fragTexCoord;
layout(location =2) in vec3 fragPosWorld;
layout(location =3) in vec3 fragNormalWorld;
layout(location =4) in flat uint id;
layout(location =5) in vec4 clipspacepos;

layout(location = 0) out vec4 outColor;
layout(location = 1) out uint outID;

struct PointLight {
    vec4 Position;
    vec4 Color;

    vec3 attenuation;// constant, linear quadratic stored in that order
};

struct DirectionalLight {
    vec3 direction;
    vec4 Color;
};

struct SpotLight {
    vec4 Position;
    vec3 direction;
    vec4 Color;
    float cutoff;
    float outerCutoff;
    vec3 attenuation;
};

//global ubo
layout(set = 0, binding = 0) uniform GlobalUBO{
    mat4 proj; //camera
    mat4 view; //camera
    vec4 ambientlightcolor;// surrounding Color
    PointLight pointlights[50]; //
    DirectionalLight DirLight[10];
    SpotLight SptLight[10];
    int activepointlights;  
    int activeDirLights;
    int activeSpotLights;
}PL;

//data from the model
layout(push_constant) uniform Push {
    mat4 modelMatrix;
    mat4 normalMatrix;
    uint textureIndex;
    float padding[3]; 
    uint id;
} push;

void main(){
    if (abs(clipspacepos.x)>1.0|| abs(clipspacepos.y)>1.0 || abs(clipspacepos.z)>1.0) discard;
    outID = id;
    int textureID = int(push.textureIndex);
    vec3 ambientlight = PL.ambientlightcolor.xyz * PL.ambientlightcolor.w;//intensity stored in w of vec4
    vec3 SurfaceNormal = normalize(fragNormalWorld);
    vec3 result = vec3(0.0,0.0,0.0);

    //sum of pointlight lighting;
    for (int i=0;i<PL.activepointlights; ++i){
        PointLight currentlight = PL.pointlights[i];
        vec3 directiontolight = currentlight.Position.xyz - fragPosWorld;
        float distance = length(directiontolight);
        directiontolight = normalize(directiontolight);
        
        //attenuation
        float attenuation = 1.0/(currentlight.attenuation.x + 
                            (currentlight.attenuation.y* distance) + 
                            (currentlight.attenuation.z* distance*distance));
        
        //diffuse
        float diff = max(dot(SurfaceNormal, directiontolight),0.0);
        vec3 diffuse = (currentlight.Color.xyz * currentlight.Color.w) * (diff * attenuation);
        
        result += diffuse;
    }
    
    //sum of Directional light lighting
    for (int i=0; i<PL.activeDirLights; ++i ){
        vec3 LightDirection = normalize(-PL.DirLight[i].direction);
        
        //diffuse
        float diff = max(dot(fragNormalWorld, LightDirection), 0.0);
        vec3 diffuse = PL.DirLight[i].Color.rgb * diff;
        
        result +=diffuse;
    }

    for (int i=0; i<PL.activeSpotLights;++i){
        SpotLight currentlight;
        vec3 LightDirection = vec3(currentlight.Position - vec4(fragPosWorld,1.0));

        //attenuation
        float distance = length(LightDirection);
        LightDirection = normalize(LightDirection);
        float attenuation = 1.0/(currentlight.attenuation.x + 
                            (currentlight.attenuation.y* distance) + 
                            (currentlight.attenuation.z* distance*distance));

        //diffuse
        float diff = max(dot(fragNormalWorld, LightDirection), 0.0);
        vec3 diffuse = (currentlight.Color.xyz * currentlight.Color.w) * (attenuation * diff);
        
        //spotlight intensity based of cutoff angle
        float theta = dot(LightDirection, normalize(-currentlight.direction));
        float epsilon = currentlight.outerCutoff - currentlight.cutoff;
        float intensity = smoothstep(epsilon, currentlight.outerCutoff, theta);

        result += diffuse * intensity;
    }

    vec4 texColor = texture(texArraySampler[textureID], fragTexCoord);
    //output finalcolor  = combination of ambient and diffuse components * texture color
    outColor = texColor * vec4((ambientlight + result), 1.0);

}