#include "power_off_button.h"
#include <iostream>

PowerButton::PowerButton()
{
}

PowerButton::PowerButton(glm::vec2 pos, glm::vec2 size, Texture2D sprite)
    :MusicPlaying(false), GameObject(pos, size, sprite, glm::vec3(1.0f, 1.0f, 1.0f))
{
}


glm::vec2 PowerButton::Click(float dt, unsigned int window_width)
{
	return glm::vec2();
}

void PowerButton::mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        std::cout << "Click" << std::endl;
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        if (xpos >= this->Position.x && xpos <= this->Position.x + this->Size.x &&
            ypos >= this->Position.y && ypos <= this->Position.y + this->Size.y) {
            std::cout << "Power" << std::endl;

            this->MusicPlaying = !this->MusicPlaying;

            if (!this->MusicPlaying) {
                this->Color = glm::vec3(1.0f);
            }
            else {
                this->Color = glm::vec3(0.0f);
            }
        }
    }
}
