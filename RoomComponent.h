#pragma once

#include "DrawComponent.h"
#include "RectangleComponent.h"
#include <vector>
#include <memory>

const float ROOM_HEIGHT = 2.0f;

class RoomComponent : public DrawComponent
{
private:
    std::vector<std::shared_ptr<RectangleComponent>> rectangles;

public:
    RoomComponent(const float sideWallsWidth, const float frontWallsWidth);
    RoomComponent(const int sideWallsWidth, const int frontWallsWidth);
    ~RoomComponent();

    virtual void draw() override;
};
