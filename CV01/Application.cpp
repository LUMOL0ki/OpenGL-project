#include "Application.h"
#include "Light.h"
#include <soil.h>
#include <filesystem>
Application* Application::instance = 0;

Application::Application()
{
	width = 1080;
	height = 800;
	window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
	xpos = 0;
	ypos = 0;
}


Application::~Application()
{
}

Application * Application::getInstance()
{
	if (instance == 0)
	{
		instance = new Application();
	}
	return instance;
}


bool Application::init(int *width, int *height) {
	glfwSetErrorCallback(Application::getInstance()->error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}
	/*
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	*/

	window = glfwCreateWindow(*width, *height, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return false;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		return false;
	}
	// get version info
	Application::getInstance()->getVersionInfo();

	glfwGetFramebufferSize(window, &*width, &*height);
	//float ratio = width / (float)height;
	glViewport(0, 0, *width, *height);
	return true;
}

void Application::error_callback(int error, const char* description) { fputs(description, stderr); }

void Application::window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void Application::window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void Application::window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void Application::cursor_pos_callback(GLFWwindow * window, double mouseX, double mouseY)
{
	glfwGetCursorPos(window, &xpos, &ypos);
	printf("cursor_pos_callback %d, %d;\n", (int)mouseX, (int)mouseY/*, (int)clickX, (int)clickY*/);
}

void Application::mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		//naètení ID a pozice ve svìtových souøadnicích
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		GLint x = (GLint)Application::getInstance()->width/2;
		GLint y = (GLint)Application::getInstance()->height/2;

		//int newy = (int)Application::getInstance()->width - y;

		glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);
		printf("Clicked on pixel % d, % d, color % 02hhx % 02hhx % 02hhx % 02hhx, depth %f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);
	}
	printf("mouseButton_callback [%d,%d,%d]\n", button, action, mode);
}
void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) 
		printf("button_callback [%d,%d,%d]\n", button, action, mode);

}

void Application::getVersionInfo()
{
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);
}

void Application::callBackFunctions() {

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {Application::getInstance()->key_callback(window, key, scancode, action, mods); });

	glfwSetErrorCallback([](int error, const char* description) -> void {Application::getInstance()->error_callback(error, description); });

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {Application::getInstance()->window_size_callback(window, width, height); });

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos) 
		-> void {
			Application::getInstance()->cursor_pos_callback(window, mouseXPos, mouseYPos); 
		});

	glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) 
		-> void {
			Application::getInstance()->mouse_button_callback(window, button, action, mods); 
		});

	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) -> void {Application::getInstance()->window_focus_callback(window, focused); });

	glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) -> void {Application::getInstance()->window_iconify_callback(window, iconified); });


}

void Application::draw() {

	Shader shader = Shader(&Camera(glm::vec3(0.0f, 0.0f, 0.0f)));
	Shader skyBox = Shader(&shader.getCamera(), Shader::ShaderType::skybox);

	std::vector<std::string> faces
	{
			"Textures/posx.jpg",
			"Textures/negx.jpg",
			"Textures/posy.jpg",
			"Textures/negy.jpg",
			"Textures/posz.jpg",
			"Textures/negz.jpg"
	};
	glActiveTexture(GL_TEXTURE0);
	GLuint skyID=skyBox.addSkyBox(faces);
	Mesh sky = Mesh(glm::vec3(0.0f, 0.0f, 0.0f), "../Models/skybox.obj");

	Light light = Light(glm::vec3(20.0f, 0.0f, 0.0f));
	Light light2 = Light(glm::vec3(4.0f, 20.0f, 0.0f));
	/*
	const int lightsnum = 2;

	Light lights[lightsnum] = {
		Light(glm::vec3(0.0f, 0.0f, 0.0f)),
		Light(glm::vec3(4.0f, 0.0f, 0.0f))
	};
	*/
	const int models = 6;

	Mesh objs[models] = {
	Mesh (glm::vec3(0.0f, 0.0f, 0.0f)),
	Mesh (glm::vec3(0.0f, 0.0f, 2.0f), "../Models/test.obj"),
	Mesh(glm::vec3(-15.0f, 0.0f, -5.0f), "../Models/test.obj"),
	Mesh(glm::vec3(-20.0f, 1.0f, -50.0f), "../Models/stone.obj"),
	Mesh(glm::vec3(10.0f, 2.0f, -50.0f), "../Models/stone.obj"),
	Mesh(glm::vec3(1.0f, 0.0f, -5.0f), "../Models/barrel.obj")
	};

	objs[2].rotate(-30, glm::vec3(0,1,0));
	Renderer renderer = Renderer();
	objs[0].scale(60);

	objs[4].rotate(30, glm::vec3(0,1, 0));
	objs[5].scale(0.5);

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	
	Camera camera = shader.getCamera();

	//camera.rotate(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//camera.translate(glm::vec3(8.0f, 0.0f, 0.0f));
	camera.translate(glm::vec3(-10.0f, 1.2f, -15.0f));
	GLint modelMatrixID = glGetUniformLocation(shader.GetShaderProgram(), "modelMatrix");
	glActiveTexture(GL_TEXTURE1);
	shader.Texture("Textures/test.png");
	
	glActiveTexture(GL_TEXTURE2);
	
	GLuint wall = shader.addTexture("Textures/ground_8K_Albedo.jpg");	

	glActiveTexture(GL_TEXTURE3);
	shader.Texture("Textures/stone_4K_Albedo.jpg");
	glActiveTexture(GL_TEXTURE4);
	shader.Texture("Textures/barrel_4K_Albedo.jpg");

	//shader.Texture("wall.jpg", 0);
	//pøidání ID do stencil bufferu
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	
	while (!glfwWindowShouldClose(window))
	{	
		// clear color and depth buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Render
		
		shader.use();
		//shader.setVec3("lightPos", glm::vec3(0, 0, 0));
		//shader.setVec3("lightColor", glm::vec3(1.5, 1.5, 1.5));

		shader.setVec3("lights[0].lightPos", light.getPosition());
		shader.setVec3("lights[0].lightColor", glm::vec3(1.5, 1.5, 1.5)); 
		shader.setVec3("lights[1].lightPos", light2.getPosition());
		shader.setVec3("lights[1].lightColor", glm::vec3(1.5, 1.5, 1.5));
		shader.setInt("numberOfLights", 2);
		//shader.setVec3("modelColor", glm::vec3(0.5, 0.1, 0.1));
		
		shader.setMat4("projectionMatrix", projection);
		camera.processInput(window, 0.25f);
		camera.mouseInput(window, 0.1f);
		shader.setMat4("viewMatrix", camera.getCamera());
		shader.setVec3("viewPos", camera.getPosition());
		
		shader.getTexture(2);
		for (int i = 0; i < models; i++) {
			glStencilFunc(GL_ALWAYS, objs[i].getVAO(), 0xFF);
			
			shader.setMat4("modelMatrix", objs[i].getMatrix());
			objs[i].render(6);
			glBindVertexArray(0);
		}
		shader.getTexture(1);
		shader.setMat4("modelMatrix", objs[1].getMatrix());
		objs[1].render();
		//objs[2].rotate(2, glm::vec3(0, 1, 0));
		//objs[2].translate(glm::vec3(1, 0, 0));
		shader.setMat4("modelMatrix", objs[2].getMatrix());
		objs[2].render();
		shader.getTexture(3);
		shader.setMat4("modelMatrix", objs[3].getMatrix());
		objs[3].render();
		shader.setMat4("modelMatrix", objs[4].getMatrix());
		objs[4].render();
		shader.getTexture(4);
		shader.setMat4("modelMatrix", objs[5].getMatrix());
		//objs[5].render();
		glDepthFunc(GL_LEQUAL); 
		skyBox.use();
		skyBox.getSkyBox(0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, skyID);
		skyBox.setMat4("projection", projection);
		skyBox.setMat4("view", glm::mat3(camera.getCamera()));
		sky.render();

		glDepthFunc(GL_LESS);
		//shader.setMat4("modelMatrix", objs[4].getMatrix());
		//objs[5].render();
		//obj1.rotate(glm::radians(1.0f), glm::vec3(0, 0, 1));
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
		
	}
}


