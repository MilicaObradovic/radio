
#include "circle_renderer.h"

#define CRES 30 // Circle Resolution = Rezolucija kruga

CircleRenderer::CircleRenderer(Shader& shader)
{
    this->shader = shader;
    this->initRenderData();
}

CircleRenderer::~CircleRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}

void CircleRenderer::DrawCircle(Texture2D& texture, glm::vec2 position, float radius, glm::vec3 color, bool isMusicPlaying)
{
    // prepare transformations
    this->shader.Use();
    float time = glfwGetTime();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f)); 
    model = glm::scale(model, glm::vec3(radius, radius, 1.0f));


    if (isMusicPlaying) {
        float vibrationFactor = sin(time * 20.0f) * 0.05f + 1.0f;
        model = glm::scale(model, glm::vec3(vibrationFactor, vibrationFactor, 1.0f));
    }

    this->shader.SetMatrix4("model", model);

    // render textured quad
    this->shader.SetVector3f("uColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLE_FAN, 0, (CRES + 2) * 2);
    glBindVertexArray(0);
}

void CircleRenderer::initRenderData()
{
    // configure VAO/VBO
    unsigned int VBO;
    float circle[(CRES + 2) * 2];
    float r = 10; //poluprecnik

    circle[0] = 0; //Centar X0
    circle[1] = 0; //Centar Y0
    int i;
    for (i = 0; i <= CRES; i++)
    {

        circle[2 + 2 * i] = r * cos((3.141592 / 180) * (i * 360 / CRES)); //Xi (Matematicke funkcije rade sa radijanima)
        circle[2 + 2 * i + 1] = r * sin((3.141592 / 180) * (i * 360 / CRES)); //Yi
    }

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(this->quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}