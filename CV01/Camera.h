#include <glm/vec2.hpp> // glm::vec4
#include <glm/vec3.hpp> // glm::vec4
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp>

#include "Object.h"

#pragma once
class Shader;
class Camera : public Object
{
private:
	glm::vec3 target;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	//Shader* m_shader;
	//glm::mat4 projection;

	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;	
	
	void updateCameraVectors();
public:
	Camera(glm::vec3 position);
	~Camera();

	glm::mat4 getCamera(void);

	//glm::mat4 getProjection();

	void moveLeft();

	void moveUp();


	
};

