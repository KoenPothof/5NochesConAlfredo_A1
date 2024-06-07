#include "TextComponent.h"
#include "GameManager.h"
#include "GameObject.h"

using tigl::Vertex;

TextComponent::TextComponent()
{
	unsigned char* ttf_buffer = new unsigned char[1 << 20];
	unsigned char* temp_bitmap = new unsigned char[512 * 512];
	fread(ttf_buffer, 1, 1 << 20, fopen("c:/windows/fonts/times.ttf", "rb"));
	stbtt_BakeFontBitmap(ttf_buffer, 0, 32.0, temp_bitmap, 512, 512, 32, 96, cdata); // no guarantee this fits!
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);
	GLint swizzleMask[] = { GL_ALPHA, GL_ALPHA, GL_ALPHA, GL_ALPHA };
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzleMask);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, 512, 512, 0, GL_ALPHA, GL_UNSIGNED_BYTE, temp_bitmap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	delete[] ttf_buffer;
	delete[] temp_bitmap;
}

TextComponent::~TextComponent()
{
}

void TextComponent::init()
{
	
}

void TextComponent::update(float deltaTime)
{
    // Update the elapsed time
    elapsedTime += deltaTime;

    // Decrease countdown every 9 seconds
    if (elapsedTime >= 9.0f) {
        countdown--;
        elapsedTime = 0.0f; // Reset elapsed time

        // Ensure countdown does not go below 0
        if (countdown < 0) {
            countdown = 0;
        }
    }
}

void TextComponent::draw()
{
    // Update the battery string to show the countdown value
    battery = "Battery Level: " + std::to_string(gameObject->gameManager->countdown);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    tigl::shader->setProjectionMatrix(glm::ortho(0.0f, (float)viewport[2], (float)viewport[3], 0.0f, -100.0f, 100.0f));
    tigl::shader->setViewMatrix(glm::mat4(1.0f));
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    tigl::shader->enableColor(false);
    tigl::shader->enableLighting(false);
    tigl::shader->enableTexture(true);
    tigl::shader->enableColorMult(true);
    tigl::shader->setColorMult(glm::vec4(1, 1, 1, 1)); // white

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, texId);

    float x1 = 10, y1 = 975;
    stbtt_aligned_quad q;
    tigl::begin(GL_QUADS);
    for (int i = 0; i < battery.size(); i++)
    {
        if (battery[i] >= 32 && battery[i] < 128)
        {
            stbtt_GetBakedQuad(cdata, 512, 512, battery[i] - 32, &x1, &y1, &q, 1); // 1=opengl & d3d10+, 0=d3d9
            tigl::addVertex(Vertex::PT(glm::vec3(q.x0, q.y0, 0), glm::vec2(q.s0, q.t0)));
            tigl::addVertex(Vertex::PT(glm::vec3(q.x1, q.y0, 0), glm::vec2(q.s1, q.t0)));
            tigl::addVertex(Vertex::PT(glm::vec3(q.x1, q.y1, 0), glm::vec2(q.s1, q.t1)));
            tigl::addVertex(Vertex::PT(glm::vec3(q.x0, q.y1, 0), glm::vec2(q.s0, q.t1)));
        }
    }
    tigl::end();

    tigl::shader->enableColor(false);
    tigl::shader->enableColorMult(false);
}