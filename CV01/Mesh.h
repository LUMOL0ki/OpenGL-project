#include <GL/glew.h>
//Include GLFW  
#include <GLFW/glfw3.h>  
#include "Object.h"

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <stdio.h>
#include <vector>
#include <string>
#include "Shader.h"
#include "Camera.h"
using namespace std;

#pragma once
/*
struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	string type;
};
*/
class Mesh : public Object
{
private:
	GLuint VAO = 0, VBO, EBO;
public:
	
	Mesh(glm::vec3 position);
	//Mesh(glm::vec3 position, vector<Vertex> vertices, vector<unsigned int> indices);
	//Mesh(glm::vec3 position, vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	~Mesh();
	void render(GLsizei count);
	GLuint getVAO();
	/*
	//  Mesh Data 
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;
	//  Functions  
	void Draw(Shader shader);
	*/
};

