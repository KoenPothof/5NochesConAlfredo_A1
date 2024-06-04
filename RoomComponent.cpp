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
    int doorWidth = 2;
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

        // rest of the walls
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // front wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // back wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        break;

	case FRONTBACK: 
		doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::FRONT));
		doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::BACK));

        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // left wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // right wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
	    break;

    case HALLWAY:
        doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::RIGHT));

        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // left wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        break;

    case STAGE:
        doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::LEFT));

        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // right wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // back wall
        break;
    case MAINROOM:
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        break;    
    case LEFTDOORCLOSED:
        doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::FRONT));

        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // left wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // back wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // right wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
        break;
    case RIGHTDOORCLOSED:
		doors.push_back(std::make_shared<DoorComponent>(frontWallsWidth, sideWallsWidth, height, 0, wallBesideDoorWidth, DoorComponent::BACK));

		rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // left wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // front wall
		rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // right wall
		rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
		rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling
		break;
    case BOTHCLOSED:
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // left wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // back wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 0, false, frontWallsWidth, height, texture.setTexture(14, 0))); // front wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, texture.setTexture(14, 0))); // right wall
        rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(1, 0))); // floor
        rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1 * sideWallsWidth, texture.setTexture(2, 0))); // ceiling

    };
}

void RoomComponent::openDoor(Door door)
{
    switch (door) {
	case LEFTDOOR:
		
	break;

	case RIGHTDOOR:
        break;
    }
	
}

void RoomComponent::closeDoor(Door door)
{
    switch (door) {
    case LEFTDOOR:

        break;

    case RIGHTDOOR:

        break;

    case BOTHDOORS:
		break;
    }
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
