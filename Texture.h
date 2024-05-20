#pragma once

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <gl/glew.h>

class Texture
{
public:
	Texture(const std::string& filename, int textureWidth, int textureHeight, int textureSize);
	~Texture();
	void bind();
	glm::vec2* setTexture(int textureX, int textureY);
private:
	unsigned int id, texture;
	int width, height, nrChannels, textureHeight, textureWidth, texturesPerRow, textureSize;
	unsigned char* data, * currentTextureData;
};


