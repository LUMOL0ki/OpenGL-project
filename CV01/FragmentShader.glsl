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

uniform vec3 modelColor;

uniform light lights[MAX_LIGHTS];

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform int numberOfLights;
uniform vec3 viewPos;

in vec3 Position;
in vec3 Normal;

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
		result += (ambient + diffuse + specular);
	}
    frag_colour =  vec4 (result, 1.0) * texture(textureUnitID, uv);// + texture(textureUnitID, uv);
}