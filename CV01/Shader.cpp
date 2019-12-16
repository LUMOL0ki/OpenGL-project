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
	init(camera, ShaderType::nonmettalic);
}

Shader::Shader(Camera* camera, ShaderType shaderType)
{
	init(camera, shaderType);
}

void Shader::init(Camera *camera, ShaderType shaderType) {
	this->m_camera = camera;
	this->shaderType = shaderType;

	createShader(this->shaderType);
	glUseProgram(shaderProgram);
	//Set texture unit to fragment shader
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



GLuint Shader::addTexture(const char *path)
{
	GLuint tex;
	
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	int width, height;
	unsigned char* image;
	//Bind the first texture to the first texture unit.
	image = SOIL_load_image(path, &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D); //Generate mipmaps now!!!
	SOIL_free_image_data(image);
	//Set texture unit to fragment shader

	return tex;
}

GLuint Shader::addSkyBox(std::vector<std::string> faces) {
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* image = SOIL_load_image(faces[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
		if (image)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);
			SOIL_free_image_data(image);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			SOIL_free_image_data(image);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return textureID;
}

void Shader::getSkyBox(int id) 
{
	GLint uniformID = glGetUniformLocation(shaderProgram, "skybox");
	glUniform1i(uniformID, id);
}

void Shader::getTexture(int id) {
	GLint uniformID = glGetUniformLocation(shaderProgram, "textureUnitID");
	glUniform1i(uniformID, id);
}

void Shader::Texture(const char* path) 
{
	GLuint textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Shader::createShader(ShaderType shaderType)
{
	ShaderLoader* loader = new ShaderLoader();
	switch (shaderType)
	{
	case nonmettalic:
		shaderProgram = loader->loadShader("./VertexShader.glsl", "./FragmentShader.glsl");
		break;
	case skybox:
		shaderProgram = loader->loadShader("./VertexSkyBox.glsl", "./FragmentSkyBox.glsl");
		break;
	case depth:
		shaderProgram = loader->loadShader("./VertexSkyBox.glsl", "./FragmentSkyBox.glsl");
	}
}
// activate the shader
// ------------------------------------------------------------------------
void Shader::use()
{
	/*GLuint framebuffer = 0, shadowMap = 0;
	if (framebuffer == 0) glGenFramebuffers(1, &framebuffer);
	if (shadowMap != 0) glDeleteTextures(1, &shadowMap);

	glActiveTexture(GL_TEXTURE1);
	glGenTextures(1, &shadowMap);
	glBindTexture(GL_TEXTURE_2D, shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 1024,
		1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//Set compare mode and function for shadow sampling
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("ERROR: Something's wrong with framebuffer.\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//definujeme oblast a vlastnosti výpoètu stínu
	glm::mat4 depthProjectionMatrix;
	glm::mat4 depthViewMatrix = getCamera().getCamera();
	*/
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