#define GLEW_STATIC
#include <GL/glew.h>
//#include <GL/eglew.h>
//#include <GL/glxew.h>
//#include <GL/wglew.h>

//Include GLFW  
#include <GLFW/glfw3.h>  

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include "Application.h"
#include "Shader.h"

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Camera.h"
#include "Mesh.h"
#include "Object.h"
#include "Renderer.h"
#include "Sphere.h"

GLFWwindow* window;
int width = 1080, height = 800;

bool loadContect(int object, const float vertices[]) {
	GLuint VBO = NULL;
	//vertex buffer object (VBO)	;
	glGenBuffers(object, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(sphere), sphere, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	return true;
}

int main(void)
{
	Application* app;
	app = app->getInstance();
	if (!app->init(&width, &height)) {
		exit(EXIT_FAILURE);
	}
	/*if (!loadContect(1, sphere)) {
		exit(EXIT_FAILURE);
	}*/
	/*if (!loadContect(2)) {
		exit(EXIT_FAILURE);
	}*/

	app->callBackFunctions();

	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f));
	Shader shader = Shader(&camera);

	app->draw(shader);
	
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}