#include "Object.h"


Object::Object(glm::vec3 position)
{
	this->position = position;
	m_matrix = glm::translate(m_matrix, position);
}

Object::~Object()
{
}

glm::mat4 Object::getMatrix()
{
	return m_matrix;
}

glm::vec3 Object::getPosition() {
	return position;
}

void Object::setPosition(glm::vec3 position)
{
	glm::vec3 tempPos;
	tempPos -= position;
	this->position = position;
	m_matrix = translate(tempPos);
}

glm::mat4 Object::translate(glm::vec3 shift)
{
	position += shift;
	m_matrix = glm::translate(m_matrix, shift);
	return m_matrix;
}

glm::mat4 Object::translate(glm::mat4 m_matrix, glm::vec3 shift)
{
	m_matrix = glm::translate(m_matrix, shift);
	return m_matrix;
}

glm::mat4 Object::rotate(float angle, glm::vec3 shift)
{
	
	m_matrix = glm::rotate(m_matrix, glm::radians(angle), shift);
	return m_matrix;
}

glm::mat4 Object::rotate(glm::mat4 m_matrix, float angle, glm::vec3 shift)
{
	m_matrix = glm::rotate(m_matrix, angle, shift);
	return m_matrix;
}

glm::mat4 Object::scale(int scale)
{
	m_matrix = glm::scale(m_matrix, glm::vec3(scale, scale, scale));
	return m_matrix;
}

glm::mat4 Object::scale(glm::vec3 scale)
{
	m_matrix = glm::scale(m_matrix, scale);
	return m_matrix;
}

glm::mat4 Object::scale(glm::mat4 m_matrix, glm::vec3 scale)
{
	m_matrix = glm::scale(m_matrix, scale);
	return m_matrix;
}
