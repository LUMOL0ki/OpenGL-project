#include "Object.h"
#include "Shader.h"

#pragma once
class Renderer
{
private:
	//Shader m_shader;
public:
	Renderer();

	void Render(Object obj, Shader shader);

	~Renderer();
};

