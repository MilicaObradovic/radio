
#include "sprite_renderer.h"
#include <iostream>

SpriteRenderer::SpriteRenderer(Shader& shader)
{
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D& texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, bool isAntenna, bool isPointer)
{
    // prepare transformations
    this->shader.Use();

    glm::mat4 model = glm::mat4(1.0f);
    //model = glm::translate(model, glm::vec3(position, 0.0f)); 
    model = glm::translate(model, glm::vec3(-47.0f, -20.0f, -2.0f));
    
    //model = glm::scale(model, glm::vec3(size, 1.0f));
    model = glm::scale(model, glm::vec3(100.0f, 40.0f, 1.0f));

    this->shader.SetMatrix4("model", model);

    // render textured quad
    this->shader.SetVector3f("uColor", glm::vec3(0.3f, 0.3f, 0.3f));

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}

void SpriteRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float vertices[] = {
        // pos
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}