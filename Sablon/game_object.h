#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <GL/glew.h>   //Omogucava laksu upotrebu OpenGL naredbi
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "sprite_renderer.h"
#include "circle_renderer.h"


class GameObject
{
public:
    // object state
    glm::vec2   Position, Size;
    float Velocity;
    glm::vec3   Color;
    float       Rotation;
    bool        IsSolid;
    bool        Destroyed;
    // render state
    Texture2D   Sprite;
    // constructor(s)
    GameObject();
    GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprite, glm::vec3 color = glm::vec3(1.0f), float velocity = 0);
    // draw sprite
    virtual void Draw(SpriteRenderer& renderer, bool isAntenna, bool isPointer);
};

#endif