#pragma once
#ifndef GAME_H
#define GAME_H
#include <vector>
#include <tuple>

#include <GL/glew.h>   //Omogucava laksu upotrebu OpenGL naredbi
#include <GLFW/glfw3.h>
class Game
{
public:
    bool                    Keys[1024];
    bool                    KeysProcessed[1024];
    unsigned int            Width, Height;
    unsigned int            Level;
    unsigned int            Lives;
    // constructor/destructor
    Game(unsigned int width, unsigned int height);
    Game();
    ~Game();
    // initialize game state (load all shaders/textures/levels)
    void Init();
    // game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render(GLFWwindow* window);
};

#endif