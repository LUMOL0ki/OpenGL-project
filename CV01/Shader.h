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
#include <iostream>	// std::cout std::cin
#include <fstream>	// std::ifstream
#include <string>	// std::string
#include <sstream>	// std::stringstream

#pragma once
class Camera;
class Shader
{
private:
	GLuint shaderProgram, vs, fs;
	Camera *m_camera;
	GLuint initShaderProgram(GLuint vertexShader, GLuint fragmentShader);
	void createShader(const std::string& vertex_shader, const std::string& fragment_shader);	GLuint compileShader(GLuint type, const std::string & source);
public:
	//Shader();
	Shader(Camera *camera, const std::string& vertex_shader, const std::string& fragment_shader);
	GLuint GetShaderProgram();
	
	Camera getCamera();

	void use();

	void sendUniform(const GLchar *name, glm::vec4 data);
	void deleteShader();
	void setBool(const std::string& name, bool value);
	void setInt(const std::string& name, int value);
	void setFloat(const std::string& name, float value);
	void setVec3(const std::string& name, glm::vec3 vector);
	void setVec4(const std::string& name, glm::vec4 vector);
	void setMat4(const std::string& name, glm::mat4 matrix);
	~Shader();
};

