#include "RectangleComponent.h"

RectangleComponent::RectangleComponent(float widthX, float widthZ, float height)
{
	// draw a triangle
	verts.push_back(Vertex::P(glm::vec3(-0.5f, -0.5f, 0.0f)));
	verts.push_back(Vertex::P(glm::vec3(0.5f, -0.5f, 0.0f)));
	verts.push_back(Vertex::P(glm::vec3(0.0f, 0.5f, 0.0f)));
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::draw()
{
	tigl::drawVertices(GL_TRIANGLES, verts);
}
