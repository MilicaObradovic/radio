#include "power_off_button.h"
#include <iostream>

PowerButton::PowerButton()
{
}

PowerButton::PowerButton(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
    :MusicPlaying(false), GameObject(pos, size, sprite, glm::vec3(0.7, 0.1, 0.1))
{
}


glm::vec2 PowerButton::Click(float dt, unsigned int window_width)
{
	return glm::vec2();
}
