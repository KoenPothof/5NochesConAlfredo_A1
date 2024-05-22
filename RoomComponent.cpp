#include "RoomComponent.h"

RoomComponent::RoomComponent(const float sideWallsWidth, const float frontWallsWidth)
{
    // Left and right walls
    //rectangles.push_back(std::make_shared<RectangleComponent>(1, false, ));
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
