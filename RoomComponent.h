#pragma once

#include "DrawComponent.h"
#include "RectangleComponent.h"
#include <vector>
#include <memory>

class RoomComponent : public DrawComponent
{
private:
    std::vector<std::shared_ptr<RectangleComponent>> rectangles;

public:
    RoomComponent(int x1, int y1, int x2, int y2, int height);
    ~RoomComponent();

    virtual void draw() override;
};
