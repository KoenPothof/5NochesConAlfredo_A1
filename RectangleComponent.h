#pragma once

#include "DrawComponent.h"
#include "tigl.h"
#include "Texture.h"
using tigl::Vertex;
#include <vector>

class RectangleComponent : public DrawComponent
{
	std::vector<Vertex> verts;
	Texture* compTexture;
public:
	RectangleComponent(int x, int y, int z, int direction, bool flat, int width, int height, glm::vec2* texturePositions);
	RectangleComponent(int x, int y, int z, int direction, bool flat, int width, int height, Texture* texture);
	~RectangleComponent();

	virtual void draw() override;
};

