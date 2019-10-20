#include "Light.h"

Light::Light(glm::vec3 position) : Object(position){
	this->position = position;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// set the vertex attributes (only position data for our lamp)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

Light::~Light() {

}

void Light::render() {
	glBindVertexArray(VAO);
}