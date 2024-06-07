#pragma once
#include "DrawComponent.h"
#include "stb_truetype.h"
#include <string>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "GameManager.h"

class TextComponent : public DrawComponent
{
public:
	stbtt_bakedchar cdata[96];
	GLuint texId;
	std::string battery = "Battery Level: ";
	

	TextComponent();
	~TextComponent();

	float countdown;
	float elapsedTime;
	float deltaTime;

	void init();
	virtual void draw() override;
	void update(float deltaTime);
};

