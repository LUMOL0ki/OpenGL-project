#include "Renderer.h"



Renderer::Renderer()
{
}

void Renderer::Render(Object obj, Shader shader)
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}


Renderer::~Renderer()
{
}
