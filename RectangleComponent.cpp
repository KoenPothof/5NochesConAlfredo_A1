#include "RectangleComponent.h"
#include "Texture.h"

extern Texture* texture;

// xyz for bottom point, direction 0 for x-as direction and direction 1 for z-as direction, for flat width is x length and height is z length
RectangleComponent::RectangleComponent(int x, int y, int z, int direction, bool flat, int width, int height, glm::vec2* texturePositions, float wallWidth, bool switchNormalDirection)
{
    glm::vec3 normalDirection = glm::vec3(1, 1, 1);
    if (switchNormalDirection)
        normalDirection = glm::vec3(-1, -1, -1);


    if (direction == 0 && flat == false) {
        verts.push_back(Vertex::PTN(glm::vec3(x, y, z), texturePositions[0], glm::vec3(0, 0, -1))); // bottom point
        verts.push_back(Vertex::PTN(glm::vec3(x + width, y, z), texturePositions[1], glm::vec3(0, 0, -1))); // far bottom point
        verts.push_back(Vertex::PTN(glm::vec3(x + width, y + height, z), texturePositions[2], glm::vec3(0, 0, -1))); // far top point
        verts.push_back(Vertex::PTN(glm::vec3(x, y + height, z), texturePositions[3], glm::vec3(0, 0, -1))); // top point

        verts.push_back(Vertex::PT(glm::vec3(x, y, z), texturePositions[0])); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x, y, z + wallWidth), texturePositions[1])); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z + wallWidth), texturePositions[2])); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z), texturePositions[3])); // top point

        verts.push_back(Vertex::PT(glm::vec3(x + width, y, z), texturePositions[0])); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y, z + wallWidth), texturePositions[1])); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y + height, z + wallWidth), texturePositions[2])); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y + height, z), texturePositions[3])); // top point

        verts.push_back(Vertex::PTN(glm::vec3(x, y, z + wallWidth), texturePositions[0], glm::vec3(0, 0, 1))); // bottom point
        verts.push_back(Vertex::PTN(glm::vec3(x + width, y, z + wallWidth), texturePositions[1], glm::vec3(0, 0, 1))); // far bottom point
        verts.push_back(Vertex::PTN(glm::vec3(x + width, y + height, z + wallWidth), texturePositions[2], glm::vec3(0, 0, 1))); // far top point
        verts.push_back(Vertex::PTN(glm::vec3(x, y + height, z + wallWidth), texturePositions[3], glm::vec3(0, 0, 1))); // top point

        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z), texturePositions[0])); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y + height, z), texturePositions[1])); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y + height, z + wallWidth), texturePositions[2])); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x, y + height, z + wallWidth), texturePositions[3])); // top point

        verts.push_back(Vertex::PT(glm::vec3(x, y, z), texturePositions[0])); // bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y, z), texturePositions[1])); // far bottom point
        verts.push_back(Vertex::PT(glm::vec3(x + width, y, z + wallWidth), texturePositions[2])); // far top point
        verts.push_back(Vertex::PT(glm::vec3(x, y, z + wallWidth), texturePositions[3])); // top point
    }
    else if (direction == 1 && flat == false) {
        verts.push_back(Vertex::PTN(glm::vec3(x, y, z), texturePositions[1], glm::vec3(-1, 0, 0) * normalDirection)); // bottom point
        verts.push_back(Vertex::PTN(glm::vec3(x, y, z - width), texturePositions[0], glm::vec3(-1, 0, 0) * normalDirection)); // far bottom point
        verts.push_back(Vertex::PTN(glm::vec3(x, y + height, z - width), texturePositions[3], glm::vec3(-1, 0, 0) * normalDirection)); // far top point
        verts.push_back(Vertex::PTN(glm::vec3(x, y + height, z), texturePositions[2], glm::vec3(-1, 0, 0) * normalDirection)); // top point
    }
    else if (flat == true) {
        verts.push_back(Vertex::PTN(glm::vec3(x, y, z), texturePositions[1], glm::vec3(0, -1, 0) * normalDirection)); // bottom point
        verts.push_back(Vertex::PTN(glm::vec3(x - width, y, z), texturePositions[0], glm::vec3(0, -1, 0) * normalDirection)); // far bottom point
        verts.push_back(Vertex::PTN(glm::vec3(x - width, y, z + height), texturePositions[3], glm::vec3(0, -1, 0) * normalDirection)); // far top point
        verts.push_back(Vertex::PTN(glm::vec3(x, y, z + height), texturePositions[2], glm::vec3(0, -1, 0) * normalDirection)); // top point
    }
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::draw()
{
    texture->bind();
	tigl::drawVertices(GL_QUADS, verts);
}
