#pragma once

#include "DrawComponent.h"
#include "tigl.h"
using tigl::Vertex;

#include <vector>

class RectangleComponent : public DrawComponent
{
	std::vector<Vertex> verts;
public:
	RectangleComponent(float widthX, float widthZ, float height);
	~RectangleComponent();


	virtual void draw() override;
};

