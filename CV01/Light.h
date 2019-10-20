#include "Object.h"
#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
#include "Object.h"

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#pragma once
class Light : public Object
{
private:
	GLuint VAO = 0;
public:
	Light(glm::vec3 position);
	~Light();
	void render();
};

