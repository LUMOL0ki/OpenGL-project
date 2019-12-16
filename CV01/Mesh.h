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

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

using namespace std;

#pragma once

struct Vertex {
	float Position[3];
	float Normal[3];
	float Texture[2];
	float Tangent[3];
};

class Mesh : public Object
{
private:
	GLuint VAO = 0, VBO, IBO = 0;
	int indicesCount = 0;
public:
	
	Mesh(glm::vec3 position);
	Mesh(glm::vec3 position, std::string fileName);
	void load(std::string fileName);
	//Mesh(glm::vec3 position, vector<Vertex> vertices, vector<unsigned int> indices);
	//Mesh(glm::vec3 position, vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	~Mesh();
	void render(GLsizei count);
	void render();
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

