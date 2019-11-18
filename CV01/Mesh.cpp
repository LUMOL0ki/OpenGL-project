#include "Mesh.h"
#include "Sphere.h"
#include "Plain.h"

Mesh::Mesh(glm::vec3 position) : Object(position){
	this->position = position;
	//vertex attribute object(VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO

	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(plain), plain, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); //Normal
	glEnableVertexAttribArray(2); //UV
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(6 * sizeof(float)));
}
/*
Mesh::Mesh(glm::vec3 position, vector<Vertex> vertices, vector<unsigned int> indices) : Object(position)
{
}

Mesh::Mesh(glm::vec3 position, vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures) : Object(position)
{
}
*/

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

/*
void Mesh::Draw(Shader shader)
{
}
*/