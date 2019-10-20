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