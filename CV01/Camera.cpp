#include "Camera.h"
#include "Shader.h"


Camera::Camera(glm::vec3 position) : Object(position)
{
	//this->m_shader = shader;
	this->position = position;
	this->target = glm::vec3(0.0f, 0.0f, 0.0f);
	this->worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
	Yaw = 0;
	Pitch = 0;
	updateCameraVectors();
}

Camera::~Camera()
{
}

glm::mat4 Camera::getCamera(void) {
	return glm::lookAt(position, position + target, up);
}

/*
glm::mat4 Camera::getProjection() {
	return projection;
}
*/
void Camera::moveLeft() {
	//cameraRight = (glm::normalize(glm::cross(up, cameraDirection)));
}

void Camera::moveUp() {
	//cameraUp = glm::cross(cameraDirection, cameraRight);
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 target;
	target.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	target.y = sin(glm::radians(Pitch));
	target.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	this->target = glm::normalize(target);
	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(this->target, worldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, this->target));
}

void Camera::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	double sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	target = glm::normalize(front);
	
}

void Camera::processInput(GLFWwindow* window, float cameraSpeed)
{
	//cameraSpeed = 0.05f; // adjust accordingly
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	double tempXpos, tempYpos;
	glfwGetCursorPos(window, &tempXpos, &tempYpos);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		position += cameraSpeed * target;
		//this->translate(cameraSpeed * target);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		position -= cameraSpeed * target;
		//this->translate(-(cameraSpeed * target));
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		position -= glm::normalize(glm::cross(target, up)) * cameraSpeed;
		//this->translate(-(glm::normalize(glm::cross(target, up)) * cameraSpeed));
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		position += glm::normalize(glm::cross(target, up)) * cameraSpeed;
		//this->translate(glm::normalize(glm::cross(target, up)) * cameraSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		position += up * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
		position -= up * cameraSpeed;
	}
	//Yaw = 12;
	//this->rotate(glm::radians(12.0f), glm::vec3(0, 1, 0));
	/*
	if (xpos != tempXpos) {
		
	}
	if (ypos != tempYpos) {
		Pitch += ypos - tempXpos;
	}
	*/
	this->updateCameraVectors();
}