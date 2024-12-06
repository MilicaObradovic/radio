
#include "radio_membrane.h"


RadioMembrane::RadioMembrane()
    : GameObject(), Radius(12.5f), MusicPlaying(true) { }

RadioMembrane::RadioMembrane(glm::vec2 pos, float radius, Texture2D sprite, float velocity )
    : GameObject(pos, glm::vec2(radius * 2.0f, radius * 2.0f), sprite, glm::vec3(0.0f, 0.0f, 0.0f), velocity), Radius(radius), MusicPlaying(true) { }

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
    renderer.DrawCircle(this->Sprite, this->Position, this->Radius,  this->Color , this->MusicPlaying, this->Velocity);

}

