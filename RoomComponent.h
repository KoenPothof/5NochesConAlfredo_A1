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
    RoomComponent(const int sideWallsWidth, const int frontWallsWidth, const int wallBesideDoorWidth);
    ~RoomComponent();

    virtual void draw() override;
};
