#pragma once
#include "DrawComponent.h"
#include "stb_truetype.h"
#include <string>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
class TextComponent : public DrawComponent
{
public:
	stbtt_bakedchar cdata[96];
	GLuint texId;
	std::string text = "Hello World";

	TextComponent();
	~TextComponent();

	void init();
	virtual void draw() override;
};

