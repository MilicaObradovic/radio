#pragma once
#ifndef CIRCLE_RENDERER_H
#define CIRCLE_RENDERER_H

#include <GL/glew.h>   //Omogucava laksu upotrebu OpenGL naredbi
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"


class CircleRenderer
{
public:
    // Constructor (inits shaders/shapes)
    CircleRenderer(Shader& shader);
    // Destructor
    ~CircleRenderer();
    // Renders a defined quad textured with given sprite
    void DrawCircle(Texture2D& texture, glm::vec2 position, float radius = 10.0f, glm::vec3 color = glm::vec3(1.0f), bool isMusicPlaying=false, float velocity = 0);
private:
    // Render state
    Shader       shader;
    unsigned int quadVAO;
    // Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();
};

#endif