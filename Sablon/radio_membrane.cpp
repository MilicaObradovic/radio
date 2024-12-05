
#include "radio_membrane.h"


RadioMembrane::RadioMembrane()
    : GameObject(), Radius(12.5f), MusicPlaying(true) { }

RadioMembrane::RadioMembrane(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite)
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(1.0f, 0.0f, 0.0f), velocity), Radius(radius), MusicPlaying(true) { }

glm::vec2 RadioMembrane::Move(float dt, unsigned int window_width)
{
    // if not stuck to player board
    if (this->MusicPlaying)
    {
        
    }
    return this->Position;
}

void RadioMembrane::Draw(CircleRenderer& renderer)
{
    renderer.DrawCircle(this->Sprite, this->Position, this->Radius,  glm::vec3(0.0f, 0.0f, 0.0f), this->MusicPlaying);

}

// resets the ball to initial Stuck Position (if ball is outside window bounds)
void RadioMembrane::Reset(glm::vec2 position, glm::vec2 velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->MusicPlaying = true;
}
