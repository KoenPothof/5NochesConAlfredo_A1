#include "RoomComponent.h"
#include "Texture.h"

extern Texture texture;

RoomComponent::RoomComponent(const int sideWallsWidth, const int frontWallsWidth, const int wallBesideDoorWidth, DoorLocation doorLocation)
{
    int height = 10;
    int x = 0;
    int y = 0;
    int z = 0;

    int doorHeight = 5;
    int doorWidth = 3;
    //int wallBesideDoorWidth = 2;

    switch (doorLocation)
    {
    case FRONT:

        doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::FRONT));

        // rest of the walls
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // left wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // back wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // right wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        break;

    case BACK:
        doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::BACK));
        
        // rest of the walls
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // front wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // left wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // right wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        break;

    case LEFT:
        doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::LEFT));

        // rest of the walls
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // front wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // back wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // right wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        break;

    case RIGHT:
        doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::RIGHT));

        // rest of the walls
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // front wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // left wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // back wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        break;

    case RIGHTLEFT:
        doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::LEFT));
        doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::RIGHT));

        // right wall with door
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth - doorWidth - wallBesideDoorWidth, height, texture.setTexture(14, 0))); // front wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y + doorHeight, z - sideWallsWidth + doorWidth + wallBesideDoorWidth, 1, false, doorWidth, height - doorHeight, texture.setTexture(14, 0))); // wall above door
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z - sideWallsWidth + wallBesideDoorWidth, 1, false, wallBesideDoorWidth, height, texture.setTexture(14, 0))); // wall beside door

        // left wall with door
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth - doorWidth - wallBesideDoorWidth, height, texture.setTexture(14, 0))); // front wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y + doorHeight, z - sideWallsWidth + doorWidth + wallBesideDoorWidth, 1, false, doorWidth, height - doorHeight, texture.setTexture(14, 0))); // wall above door
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth + wallBesideDoorWidth, 1, false, wallBesideDoorWidth, height, texture.setTexture(14, 0))); // wall beside door

        // rest of the walls
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // front wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // back wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        break;
    };
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
    for (const auto& door : doors)
    {
        door->draw();
    }
}
