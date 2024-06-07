#pragma once

#include "DrawComponent.h"
#include "tigl.h"
#include "fbo.h"
using tigl::Vertex;
#include <vector>

class ScreenComponent : public DrawComponent
{
	std::vector<Vertex> verts;
	Fbo* fbo;
public:
	ScreenComponent(int x, int y, int z, int direction, bool flat, int width, int height, Fbo* fbo);
	~ScreenComponent();

	virtual void draw() override;
};

