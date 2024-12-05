#pragma once
#ifndef BUTTONOBJECT_H
#define BALLOBUTTONOBJECT_HBJECT_H

#include <GL/glew.h>   //Omogucava laksu upotrebu OpenGL naredbi
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"


class PowerButton : public GameObject
{
public:
    bool    MusicPlaying;
    // constructor(s)
    PowerButton();
    PowerButton(glm::vec2 pos, glm::vec2 size, Texture2D sprite);
    glm::vec2 Click(float dt, unsigned int window_width);
    void mouse_callback(GLFWwindow* window, int button, int action, int mods);

};

#endif