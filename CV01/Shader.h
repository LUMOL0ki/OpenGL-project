#include <GL/glew.h>
#include <GLFW/glfw3.h> 
//Include GLM  
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//#include "glutwindow.h"
//#include "glsl.h"

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include <iostream>	// std::cout std::cin
#include <fstream>	// std::ifstream
#include <string>	// std::string
#include <sstream>	// std::stringstream
#include <vector>

#pragma once
class Camera;
class Shader
{
public:
	enum ShaderType
	{
		mettalic,
		nonmettalic,
		skybox,
		depth
	};
private:
	GLuint shaderProgram, vs, fs;
	Camera *m_camera;
	ShaderType shaderType;
	void createShader(ShaderType shaderType);
public:
	//Shader();
	Shader(Camera *camera);
	Shader(Camera* camera, ShaderType shaderType);
	void init(Camera* camera, ShaderType shaderType);
	GLuint GetShaderProgram();
	
	Camera getCamera();

	GLuint addTexture(const char *path);

	GLuint addSkyBox(std::vector<std::string> faces);

	void getSkyBox(int id);

	void getTexture(int id);

	void Texture(const char* path);

	void use();

	void sendUniform(const GLchar *name, glm::vec4 data);
	void deleteShader();
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVec3(const std::string& name, glm::vec3 vector);
	void setVec4(const std::string& name, glm::vec4 vector);
	void setMat4(const std::string& name, glm::mat4 matrix);
	void setLight(const std::string& name, bool value);
	~Shader();
};

