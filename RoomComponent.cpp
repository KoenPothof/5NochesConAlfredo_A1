#include "RoomComponent.h"

RoomComponent::RoomComponent(const int sideWallsWidth, const int frontWallsWidth)
{
    // Left and right walls
    //rectangles.push_back(std::make_shared<RectangleComponent>(1, false, ));

    int height = 10;
    int x = 0;
    int y = 0;
    int z = 0;

    rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 0, false, frontWallsWidth, height)); // front wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height)); // right wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z - sideWallsWidth, 0, false, frontWallsWidth, height)); // back wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height)); // left wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1*sideWallsWidth)); // floor
    rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1*sideWallsWidth)); // ceiling
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
