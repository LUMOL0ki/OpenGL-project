#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
#include "Object.h"

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdio.h>
#pragma once

class Mesh : public Object
{
private:
	GLuint VAO = 0;
public:
	
	Mesh(glm::vec3 position);
	~Mesh();
	void render(GLsizei count);
	GLuint getVAO();
};

