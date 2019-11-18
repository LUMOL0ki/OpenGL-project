#version 430

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location=0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
out vec3 Position;
out vec3 Normal;
out vec2 uv;

void main () {
     gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4 (aPosition, 1.0);
	 Position = vec3(modelMatrix*vec4(aPosition, 1.0));
	 Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;
	 uv = aUV;
}
