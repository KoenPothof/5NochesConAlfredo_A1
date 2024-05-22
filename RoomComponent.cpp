#include "RoomComponent.h"

RoomComponent::RoomComponent(int x1, int y1, int x2, int y2, int height)
{
    // Bottom wall
    rectangles.push_back(std::make_shared<RectangleComponent>(0, true, x2 - x1, height));

    // Top wall
    rectangles.push_back(std::make_shared<RectangleComponent>(0, true, x2 - x1, height));

    // Left wall
    rectangles.push_back(std::make_shared<RectangleComponent>(90, true, y2 - y1, height));

    // Right wall
    rectangles.push_back(std::make_shared<RectangleComponent>(90, true, y2 - y1, height));

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
