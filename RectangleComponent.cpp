#include "RectangleComponent.h"

// xyz for bottom point, direction 0 for x-as direction and direction 1 for z-as direction, for flat width is x length and height is z length
RectangleComponent::RectangleComponent(int x, int y, int z, int direction, bool flat, int width, int height, glm::vec2* texturePositions) : compTexture(new Texture("assets/screen.jpg", 800, 600, NULL))
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

RectangleComponent::RectangleComponent(int x, int y, int z, int direction, bool flat, int width, int height, Texture* texture) : compTexture(texture)
{
    glm::vec2 pos1 = glm::vec2(0, 0);
    glm::vec2 pos2 = glm::vec2(1, 0);
    glm::vec2 pos3 = glm::vec2(1, 1);
    glm::vec2 pos4 = glm::vec2(0, 1);

    if (direction == 0 && flat == false) {
        verts.push_back(Vertex::PT(glm::vec3(x, y, z), pos1)); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y, z), pos2)); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y + height, z), pos3)); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z), pos4)); // top point
    }
    else if (direction == 1 && flat == false) {
        verts.push_back(Vertex::PT(glm::vec3(x, y, z), pos2)); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x, y, z - width), pos1)); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z - width), pos4)); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z), pos3)); // top point
    }
    else if (flat == true) {
        verts.push_back(Vertex::PT(glm::vec3(x, y, z), pos2)); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x - width, y, z), pos1)); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x - width, y, z + height), pos4)); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x, y, z + height), pos3)); // top point
    }
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::draw()
{
    compTexture->bind();
	tigl::drawVertices(GL_QUADS, verts);
}