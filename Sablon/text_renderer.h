#pragma once
#ifndef TEXT_RENDERER_H
#define TEXT_RENDERER_H

#include <map>
#include <GL/glew.h>   //Omogucava laksu upotrebu OpenGL naredbi
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "texture.h"
#include "shader.h"


/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

class TextRenderer
{
public:
    // holds a list of pre-compiled Characters
    std::map<char, Character> Characters;
    // shader used for text rendering
    Shader TextShader;
    // constructor
    TextRenderer(unsigned int width, unsigned int height);
    // pre-compiles a list of characters from the given font
    void Load(std::string font, unsigned int fontSize);
    // renders a string of text using the precompiled list of characters
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f), glm::vec2 position = glm::vec2(0.0f));
    void RenderChar(Character ch, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f), glm::vec2 position = glm::vec2(0.0f));
    void RenderTextLetterByLetter(std::string text, float startX, float y, float scale, glm::vec3 color, float speed, float threshold, float resetPosition, float deltaTime);
    void RenderMovingText(float& x, float resetPosition, float threshold, float speed);

private:
    // render state
    unsigned int VAO, VBO;
};

#endif 