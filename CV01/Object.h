//#include "Mesh.h"
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#pragma once
class Object
{
private:
	//Mesh m_mesh;
	protected:
	glm::vec3 position;
	glm::mat4 m_matrix = glm::mat4(1.0f);

public:
	Object(glm::vec3 position);
	~Object();

	//Mesh getMesh();

	glm::mat4 getMatrix();

	glm::vec3 getPosition();

	glm::mat4 translate(glm::vec3 shift);
	static glm::mat4 translate(glm::mat4 model, glm::vec3 shift);
	glm::mat4 rotate(float angle, glm::vec3 shift);
	static glm::mat4 rotate(glm::mat4 model, float angle, glm::vec3 shift);
	glm::mat4 scale(glm::vec3 scale);
	static glm::mat4 scale(glm::mat4 model, glm::vec3 scale);
};

