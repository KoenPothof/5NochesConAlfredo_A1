#include "RoomComponent.h"
#include "Texture.h"

extern Texture texture;

RoomComponent::RoomComponent(const int sideWallsWidth, const int frontWallsWidth)
{
    // Left and right walls
    //rectangles.push_back(std::make_shared<RectangleComponent>(1, false, ));

    int height = 10;
    int x = 0;
    int y = 0;
    int z = 0;

    rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 0, false, frontWallsWidth, height, texture.setTexture(0, 0))); // front wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, texture.setTexture(0, 0))); // right wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, texture.setTexture(0, 0))); // back wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, texture.setTexture(0, 0))); // left wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1*sideWallsWidth, texture.setTexture(1, 0))); // floor
    rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1*sideWallsWidth, texture.setTexture(2, 0))); // ceiling
}

RoomComponent::~RoomComponent()
{
}

void RoomComponent::draw()
{
    for (const auto& rectangle : rectangles)
    {
        rectangle->draw();
    }
}
