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

	//Bind the first texture to the first texture unit.
	glActiveTexture(GL_TEXTURE0);
	GLuint textureID = SOIL_load_OGL_texture("test.png", SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);
	textureID++;

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

void Shader::addTexture(const char *path)
{
	GLuint textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);
	textureID++;
}
/*
void Shader::Texture(const char* path) {
	/*cv::Mat image;
	image = cv::imread("../wooden_planks.jpg", 1); //load the image (RGB format)
	cv::imshow("im1",image);
	cv::flip(image, image, 0); //corect orientation
	
	GLuint textureID = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glGenTextures(1, &textureID); //reference to texture
	glActiveTexture(GL_TEXTURE0); //active texture unit 0
	glBindTexture(GL_TEXTURE_2D, textureID); //object texture_id is 2D texture
	glTexImage2D(GL_TEXTURE_2D, // Type of texture 1D, 2D, 3D
		0, // Pyramid level (for mip-mapping) - 0 is the top level
		GL_RGB, // Internal colour format to convert to
		image.cols, // Image width i.e. 640
		image.rows, // Image height i.e. 480
		0, // Border width in pixels (can either be 1 or 0)
		GL_BGR, // Input format (GL_RGB, GL_RGBA, GL_BGR etc.)
		GL_UNSIGNED_BYTE, // Image data type
		image.ptr()); // The actual image data itself
	glGenerateMipmap(GL_TEXTURE_2D); //Generate mipmaps now!!!
	image.release(); //release image file
	glUniform1i(glGetUniformLocation(shaderProgram, "textura"), 0);
}
*/
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