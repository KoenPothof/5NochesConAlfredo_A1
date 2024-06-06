#include "ScreenComponent.h"

ScreenComponent::ScreenComponent(int x, int y, int z, int direction, bool flat, int width, int height, Fbo* fbo) : fbo(fbo)
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

ScreenComponent::~ScreenComponent()
{
}

void ScreenComponent::draw()
{
    fbo->bindTexture();
    tigl::drawVertices(GL_QUADS, verts);
}