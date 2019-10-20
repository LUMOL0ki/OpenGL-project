#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "Renderer.h"

#include <stdio.h>
#pragma once
class Application
{
private:
	GLFWwindow* window;
	static Application* instance;
	float width, height;
	Application();
public:
	
	
	~Application();
	static Application* getInstance();
	bool init(int *width, int *height);
	static void error_callback(int error, const char * description);
	static void window_focus_callback(GLFWwindow * window, int focused);
	static void window_iconify_callback(GLFWwindow * window, int iconified);
	static void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	static void window_size_callback(GLFWwindow * window, int width, int height);
	static void cursor_pos_callback(GLFWwindow* window, double mouseX, double mouseY);
	static void button_callback(GLFWwindow * window, int button, int action, int mode);
	static void getVersionInfo();
	//static void inputInfo(GLFWwindow* &window);
	void callBackFunctions();
	void draw(Shader shader);
};

