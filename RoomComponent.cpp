#include "RoomComponent.h"
#include "Texture.h"

extern Texture texture;

RoomComponent::RoomComponent(const int sideWallsWidth, const int frontWallsWidth)
{
    // Left and right walls
    //rectangles.push_back(std::make_shared<RectangleComponent>(1, false, ));

    Texture textureFloor = Texture("assets/floor.png", 128, 128, NULL);
    Texture textureWall = Texture("assets/wall.png", 128, 128, NULL);
    Texture textureCeiling = Texture("assets/ceiling.png", 128, 128, NULL);

    int height = 10;
    int x = 0;
    int y = 0;
    int z = 0;

    rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 0, false, frontWallsWidth, height, textureWall)); // front wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z, 1, false, sideWallsWidth, height, textureWall)); // right wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x - frontWallsWidth, y, z - sideWallsWidth, 0, false, frontWallsWidth, height, textureWall)); // back wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, false, sideWallsWidth, height, textureWall)); // left wall
    rectangles.push_back(std::make_shared<RectangleComponent>(x, y, z, 1, true, frontWallsWidth, -1*sideWallsWidth, textureFloor)); // floor
    rectangles.push_back(std::make_shared<RectangleComponent>(x, height, z, 1, true, frontWallsWidth, -1*sideWallsWidth, textureCeiling)); // ceiling
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
