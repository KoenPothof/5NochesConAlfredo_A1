#include "RoomComponent.h"

RoomComponent::RoomComponent(const int sideWallsWidth, const int frontWallsWidth)
{
    int height = 15;
    int x = 0;
    int y = 0;
    int z = 0;

    int doorHeight = 5;
    int doorWidth = 3;
    int wallBesideDoorWidth = 15;

    // front wall with door
    rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 0, false, frontWallsWidth - doorWidth - wallBesideDoorWidth, height)); // wall with door
    rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth + doorWidth + wallBesideDoorWidth, y + doorHeight, z, 0, false, doorWidth, height - doorHeight)); // wall above door door
    rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth + wallBesideDoorWidth, y, z, 0, false, wallBesideDoorWidth, height)); // wall above door door

    // front wall without door
    //rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 0, false, frontWallsWidth, height)); // front wall

    // rest of the walls
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
