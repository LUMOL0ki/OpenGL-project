#include "Shader.h"
#include "Camera.h"
/*
Shader::Shader()
{
}
*/
Shader::Shader(Camera *camera, const std::string& vertex_shader, const std::string& fragment_shader)
{
	this->m_camera = camera;
	createShader(vertex_shader, fragment_shader);
	glUseProgram(shaderProgram);
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

GLuint Shader::initShaderProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);
	return shaderProgram;
}

GLuint Shader::compileShader(GLuint type, const std::string& source)
{
	// creates an empty shader obj, ready to accept source-code and be compiled
	GLuint hShader = glCreateShader(type);

	// hands the shader source code to the shader object so that it can keep a copy of it
	const char* src = source.c_str();
	glShaderSource(hShader, 1, &src, nullptr);

	// compiles whatever source code is contained in the shader object
	glCompileShader(hShader);

	// Error Handling: Check whether the shader has been compiled
	GLint result;
	glGetShaderiv(hShader, GL_COMPILE_STATUS, &result);	// assigns result with compile operation status
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(hShader, GL_INFO_LOG_LENGTH, &length); // assigns length with length of information log
		char* infoLog = (char*)_malloca(length * sizeof(char));	// allocate on stack frame of caller
		glGetShaderInfoLog(hShader, length, &length, infoLog);	// returns the information log for a shader object
		std::cout << "Failed to compile shader!"
			<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			<< std::endl;
		std::cout << infoLog << std::endl;
		glDeleteShader(hShader);
		return static_cast<GLuint>(0);
	}

	return hShader;
}

void Shader::createShader(const std::string& vertex_shader, const std::string& fragment_shader)
{
	vs = compileShader(GL_VERTEX_SHADER, vertex_shader);
	fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader);
	shaderProgram = initShaderProgram(vs, fs);

	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		infoLogLength += 1;
		GLchar *strInfoLog = new GLchar[infoLogLength];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		glDeleteProgram(shaderProgram);
	}
	//fprintf(stderr, "Shader program: %d\n", shaderProgram);
	glValidateProgram(shaderProgram);
	// deletes intermediate objects
	glDeleteShader(vs);
	glDeleteShader(fs);

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
// ------------------------------------------------------------------------
void Shader::setInt(const std::string& name, int value)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}
// ------------------------------------------------------------------------
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