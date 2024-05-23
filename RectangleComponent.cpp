#include "RectangleComponent.h"

// xyz for bottom point, direction 0 for x-as direction and direction 1 for z-as direction, for flat width is x length and height is z length
RectangleComponent::RectangleComponent(int x, int y, int z, int direction, bool flat, int width, int height)
{
    if (direction == 0 && flat == false) {
        verts.push_back(Vertex::P(glm::vec3(x, y, z))); // bottom point
        verts.push_back(Vertex::P(glm::vec3(x - width, y, z))); // far bottom point
        verts.push_back(Vertex::P(glm::vec3(x - width, y + height, z))); // far top point
        verts.push_back(Vertex::P(glm::vec3(x, y + height, z))); // top point
    }
    else if (direction == 1 && flat == false) {
        verts.push_back(Vertex::P(glm::vec3(x, y, z))); // bottom point
        verts.push_back(Vertex::P(glm::vec3(x, y, z - width))); // far bottom point
        verts.push_back(Vertex::P(glm::vec3(x, y + height, z - width))); // far top point
        verts.push_back(Vertex::P(glm::vec3(x, y + height, z))); // top point
    }
    else if (flat == true) {
        verts.push_back(Vertex::P(glm::vec3(x, y, z))); // bottom point
        verts.push_back(Vertex::P(glm::vec3(x - width, y, z))); // far bottom point
        verts.push_back(Vertex::P(glm::vec3(x - width, y, z + height))); // far top point
        verts.push_back(Vertex::P(glm::vec3(x, y, z + height))); // top point
    }
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::draw()
{
	tigl::drawVertices(GL_QUADS, verts);
}
