#pragma once

#include "DrawComponent.h"
#include "tigl.h"
using tigl::Vertex;

#include <vector>

class RectangleComponent : public DrawComponent
{
	std::vector<Vertex> verts;
public:
	RectangleComponent(int x, int y, int z, int direction, bool flat, int width, int height, glm::vec2* texturePositions);
	~RectangleComponent();

	virtual void draw() override;
};

