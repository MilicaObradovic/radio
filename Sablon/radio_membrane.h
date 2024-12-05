#pragma once
#ifndef BALLOBJECT_H
#define BALLOBJECT_H

#include <GL/glew.h>   //Omogucava laksu upotrebu OpenGL naredbi
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "game_object.h"
#include "texture.h"


class RadioMembrane : public GameObject
{
public:
    // ball state	
    float   Radius;
    bool    MusicPlaying;
    // constructor(s)
    RadioMembrane();
    RadioMembrane(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);
    glm::vec2 Move(float dt, unsigned int window_width);
    void      Reset(glm::vec2 position, glm::vec2 velocity);
    virtual void Draw(CircleRenderer& renderer);

};

#endif