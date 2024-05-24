#include "RectangleComponent.h"

// xyz for bottom point, direction 0 for x-as direction and direction 1 for z-as direction, for flat width is x length and height is z length
RectangleComponent::RectangleComponent(int x, int y, int z, int direction, bool flat, int width, int height)
{
    if (direction == 0 && flat == false) {
        verts.push_back(Vertex::PT(glm::vec3(x, y, z), texturePositions[0])); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y, z), texturePositions[1])); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y + height, z), texturePositions[2])); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z), texturePositions[3])); // top point
    }
    else if (direction == 1 && flat == false) {
        verts.push_back(Vertex::PT(glm::vec3(x, y, z), texturePositions[1])); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x, y, z - width), texturePositions[0])); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z - width), texturePositions[3])); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z), texturePositions[2])); // top point
    }
    else if (flat == true) {
        verts.push_back(Vertex::PT(glm::vec3(x, y, z), texturePositions[1])); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x - width, y, z), texturePositions[0])); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x - width, y, z + height), texturePositions[3])); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x, y, z + height), texturePositions[2])); // top point
    }
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::draw()
{
	tigl::drawVertices(GL_QUADS, verts);
}
