#version 330

#define MAX_LIGHTS 4 
#define MAX_TEXTURES 24
struct light
{
  vec3 lightPos;
  vec3 lightColor;
};

out vec4 frag_colour;
uniform sampler2D textureUnitID;

in vec2 uv;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform vec3 modelColor;

uniform light lights[MAX_LIGHTS];

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform int numberOfLights;
uniform vec3 viewPos;

in vec3 Position;
in vec3 ShadowPosition;
in vec3 Normal;
/*
float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    if(projCoords.z > 1.0)
        shadow = 0.0;
        
    return shadow;
}
*/
void main () {
	float ambientStrength = 0.1;
	float specularStrength = 0.9;
	vec3 result;
	for(int index = 0; index < numberOfLights; index++) // for all light sources
	{
		vec3 norm = normalize(Normal);
		vec3 lightDir = normalize(lights[index].lightPos - Position);
		vec3 viewDir = normalize(viewPos - Position);
		vec3 reflectDir = -reflect(lightDir, norm); 
		float diff = max(dot(norm, lightDir), 0.0);
		vec3 diffuse = diff * lights[index].lightColor;
		vec3 ambient = ambientStrength * lights[index].lightColor;
		float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
		vec3 specular = specularStrength * spec * lights[index].lightColor;
        //float shadow = ShadowCalculation(fs_in.FragPosLightSpace); 
        //result += (ambient + (1.0 - shadow) * (diffuse + specular)) * color; 
		result += (ambient + diffuse + specular);
	}
    frag_colour =  vec4 (result, 1.0) * texture(textureUnitID, uv);// + texture(textureUnitID, uv);
}