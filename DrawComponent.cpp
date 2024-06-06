#include "DrawComponent.h"

DrawComponent::DrawComponent()
{
}

DrawComponent::~DrawComponent()
{
}

Texture DrawComponent::getTexture() {
    return Texture(Texture("assets/screen.jpg", 800, 600, NULL)); // Return a default-constructed Texture object
}
