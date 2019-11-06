#include "Application.h"
#include "Light.h"
Application* Application::instance = 0;

Application::Application()
{
	width = 1080;
	height = 800;
	window = glfwCreateWindow(width, height, "ZPG", NULL, NULL);
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
	printf("cursor_pos_callback %d, %d;\n", (int)mouseX, (int)mouseY/*, (int)clickX, (int)clickY*/);
}

void Application::button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
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
/*
void Application::inputInfo(GLFWwindow* &window) {
	// Sets the key callback
	glfwSetKeyCallback(window, Application::getInstance()->key_callback);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos)
		-> void {Application::getInstance()->cursor_pos_callback(window, mouseXPos, mouseYPos); });

	glfwSetMouseButtonCallback(window, Application::getInstance()->button_callback);

	glfwSetWindowFocusCallback(window, Application::getInstance()->window_focus_callback);

	glfwSetWindowIconifyCallback(window, Application::getInstance()->window_iconify_callback);

	glfwSetWindowSizeCallback(window, Application::getInstance()->window_size_callback);

}
*/
void Application::callBackFunctions() {

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) -> void {Application::getInstance()->key_callback(window, key, scancode, action, mods); });

	glfwSetErrorCallback([](int error, const char* description) -> void {Application::getInstance()->error_callback(error, description); });

	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) -> void {Application::getInstance()->window_size_callback(window, width, height); });

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double mouseXPos, double mouseYPos) -> void {Application::getInstance()->cursor_pos_callback(window, mouseXPos, mouseYPos); });

	//glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) -> void {Application::getInstance()->mouse_button_callback(window, button, action, mods); });

	glfwSetWindowFocusCallback(window, [](GLFWwindow* window, int focused) -> void {Application::getInstance()->window_focus_callback(window, focused); });

	glfwSetWindowIconifyCallback(window, [](GLFWwindow* window, int iconified) -> void {Application::getInstance()->window_iconify_callback(window, iconified); });


}

void Application::draw(Shader shader) {
	Light light = Light(glm::vec3(0.0f, 0.0f, 0.0f));
	Mesh objs[4] = {
	Mesh(glm::vec3(2.0f, 0.0f, 0.0f), 1),
	Mesh(glm::vec3(-2.0f, 0.0f, 0.0f), 2),
	Mesh(glm::vec3(0.0f, 2.0f, 0.0f), 3),
	Mesh(glm::vec3(0.0f, -2.0f, 0.0f), 4)
	};

	Mesh obj1 = Mesh(glm::vec3(0.0f, 0.0f, 0.0f), 1);
	Mesh obj2 = Mesh(glm::vec3(0.0f, 0.0f, 0.0f), 2);
	Mesh obj3 = Mesh(glm::vec3(0.0f, 0.0f, 0.0f), 3);
	Mesh obj4 = Mesh(glm::vec3(0.0f, 0.0f, 0.0f), 4);

	Renderer renderer = Renderer();
	obj1.translate(glm::vec3(2.0f, 0.0f, 0.0f));
	//obj1.rotate(-50, glm::vec3(0, 0, 1));
	obj2.translate(glm::vec3(-2.0f, 0.0f, 0.0f));
	
	obj3.translate(glm::vec3(0.0f, 2.0f, 0.0f));
	obj4.translate(glm::vec3(0.0f, -2.0f, 0.0f));
	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
	
	Camera camera = shader.getCamera();

	//camera.rotate(glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//camera.translate(glm::vec3(8.0f, 0.0f, 0.0f));
	camera.translate(glm::vec3(0.0f, 0.0f, -8.0f));
	GLint modelMatrixID = glGetUniformLocation(shader.GetShaderProgram(), "modelMatrix");

	glEnable(GL_DEPTH_TEST);

	//pøidání ID do stencil bufferu
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	//model = Object::scale(model, glm::vec3(0.5f));
	while (!glfwWindowShouldClose(window))
	{
		// clear color and depth buffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//obj.translate(glm::vec3(-0.005f, 0.0f, 0.0f));
		//model = glm::translate(model, glm::vec3(-0.005f, 0.0f, 0.0f));
		//obj.rotate(0.01f, glm::vec3(0.0f, 0.0f, 1.0f));
		//camera.rotate(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
		//Render
		
		shader.use();
		//camera.translate(glm::vec3(0.0f, 0.0f, 0.02f));
		shader.setVec3("lightPos", glm::vec3(0, 0, 0));
		shader.setVec3("lightColor", glm::vec3(1.5, 1.5, 1.5));
		shader.setVec3("modelColor", glm::vec3(0.5, 0.1, 0.1));
		
		shader.setMat4("projectionMatrix", projection);
		camera.processInput(window, 0.25f);
		camera.mouseInput(window, 0.1f);
	
		shader.setMat4("viewMatrix", camera.getCamera());
		shader.setVec3("viewPos", camera.getPosition());

		//obj1.rotate(glm::radians(1.0f), glm::vec3(0, 1, 0));
		
		//naètení ID a pozice ve svìtových souøadnicích
		GLbyte color[4];
		GLfloat depth;
		GLuint index;

		GLint x = (GLint)cursor.x;
		GLint y = (GLint)cursor.y;

		int newy = (int)Application::getInstance().;

		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		printf("Clicked on pixel % d, % d, color % 02hhx % 02hhx % 02hhx % 02hhx, depth %f, stencil index % u\n", x, y, color[0], color[1], color[2], color[3], depth, index);


		for (int i = 0; i < 4; i++) {
			glStencilFunc(GL_ALWAYS, objs[i].getId(), 0xFF);
			shader.setMat4("modelMatrix", objs[i].getMatrix());
			objs[i].render(2880);
			glBindVertexArray(0);
		}
		/*
		shader.setMat4("modelMatrix", obj1.getMatrix());
		obj1.render(2880);
		shader.setMat4("modelMatrix", obj2.getMatrix());
		obj2.render(2880);
		shader.setMat4("modelMatrix", obj3.getMatrix());
		obj3.render(2880);
		shader.setMat4("modelMatrix", obj4.getMatrix());
		obj4.render(2880);*/
		

		//obj1.rotate(glm::radians(1.0f), glm::vec3(0, 0, 1));
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
		
	}
}


