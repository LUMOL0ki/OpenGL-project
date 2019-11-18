#include "Shader.h"
#include "Camera.h"
#include "../Shaders/ShaderLoader.h"
#include "soil.h"
/*
Shader::Shader()
{
}
*/
Shader::Shader(Camera *camera)
{
	this->m_camera = camera;
	createShader();
	glUseProgram(shaderProgram);

	GLuint textureID = SOIL_load_OGL_texture("wall.JPG", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	//Bind the first texture to the first texture unit.
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Set texture unit to fragment shader
	GLint uniformID = glGetUniformLocation(shaderProgram, "textureUnitID");
	glUniform1i(uniformID, 0);
}

Shader::~Shader()
{
	if (shaderProgram != 0)
	{
		glDeleteProgram(shaderProgram);
	}
}

GLuint Shader::GetShaderProgram()
{
	return this->shaderProgram;
}

Camera Shader::getCamera()
{
	return *m_camera;
}

void Shader::createShader()
{
	ShaderLoader* loader = new ShaderLoader();
	shaderProgram = loader->loadShader("./VertexShader.glsl", "./FragmentShader.glsl");
}
// activate the shader
// ------------------------------------------------------------------------
void Shader::use()
{
	glUseProgram(shaderProgram);
}

void Shader::sendUniform(const GLchar *name, glm::vec4 data) {
	GLint uniformID = glGetUniformLocation(this->shaderProgram, name);
	if (uniformID >= 0) {
		glUniform4f(uniformID, data.x, data.y, data.z, data.w);
	}
	else {
		// in shader doesn't exist uniform variable 
	}
}

void Shader::deleteShader() {
	printf("ShaderLoader::deleteShader()\n");
	glDetachShader(shaderProgram, vs);
	glDetachShader(shaderProgram, fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glUseProgram(0);
	glDeleteProgram(this->shaderProgram);

}

void Shader::setBool(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, glm::vec3 vector) {
	glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), vector.x, vector.y, vector.z);
}

void Shader::setVec4(const std::string& name, glm::vec4 vector) {
	glUniform4f(glGetUniformLocation(shaderProgram, name.c_str()), vector.x, vector.y, vector.z, vector.w);
}

void Shader::setMat4(const std::string& name, glm::mat4 matrix) {
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::setLight(const std::string& name, bool value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}