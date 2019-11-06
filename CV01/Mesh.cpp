#include "Mesh.h"

Mesh::Mesh(glm::vec3 position) : Object(position){
	this->position = position;
	//vertex attribute object(VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //Normal

	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

Mesh::Mesh(glm::vec3 position, int id) : Object(position) {
	this->position = position;
	this->id = id;
	//vertex attribute object(VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //Normal
	
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
}

Mesh::~Mesh()
{
}

void Mesh::render(GLsizei count) {
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, count);
}

GLuint Mesh::getVAO()
{
	return VAO;
}

int Mesh::getId() {
	return id;
}
