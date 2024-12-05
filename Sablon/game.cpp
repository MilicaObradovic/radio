
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "radio_membrane.h"
#include "circle_renderer.h"
#include "power_off_button.h"


// Game-related State data
SpriteRenderer* Renderer;
CircleRenderer* MembraneRenderer;
SpriteRenderer* LightRenderer;
SpriteRenderer* ButtonRenderer;

CircleRenderer* CRenderer;
GameObject* Radio;
GameObject* Light;
PowerButton* PowerOffButton;
RadioMembrane* Membrane;
RadioMembrane* Bass;


Game::Game(unsigned int width, unsigned int height)
    : Keys(), Width(width), Height(height)
{

}

Game::Game()
{
}

Game::~Game()
{
    delete Renderer;
    delete Radio;
    delete Membrane;
    delete CRenderer;
    delete Light;
    delete PowerOffButton;
    delete ButtonRenderer;
    delete MembraneRenderer;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("sprite.vs", "sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("basic.vs", "basic.frag", nullptr, "basic");
    ResourceManager::LoadShader("basic.vs", "light.frag", nullptr, "light");
    ResourceManager::LoadShader("basic.vs", "membrane.frag", nullptr, "membrane");


    // configure shaders
    float timeValue = glfwGetTime(); // Get the current time
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),
        static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use().SetInteger("image", 0);
    ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
    ResourceManager::GetShader("basic").Use();
    ResourceManager::GetShader("basic").SetMatrix4("projection", projection);
    ResourceManager::GetShader("membrane").Use();
    ResourceManager::GetShader("membrane").SetMatrix4("projection", projection);
    ResourceManager::GetShader("light").Use();
    ResourceManager::GetShader("light").SetMatrix4("projection", projection);
    ResourceManager::GetShader("light").SetFloat("time", timeValue);

    // set render-specific controls
    Shader shader = ResourceManager::GetShader("sprite");
    Shader basicShader = ResourceManager::GetShader("basic");
    Shader lightShader = ResourceManager::GetShader("light");
    Shader membraneShader = ResourceManager::GetShader("membrane");

    Renderer = new SpriteRenderer(shader);
    LightRenderer = new SpriteRenderer(lightShader);
    CRenderer = new CircleRenderer(basicShader);
    ButtonRenderer = new SpriteRenderer(basicShader);
    MembraneRenderer = new CircleRenderer(membraneShader);

    // load textures
    ResourceManager::LoadTexture("wood3.jpg", true, "radio");
    ResourceManager::LoadTexture("awesomeface.png", true, "face");


    Radio = new GameObject(glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f),
        ResourceManager::GetTexture("radio"));
    PowerOffButton = new PowerButton(glm::vec2(600.0f, 210.0f), glm::vec2(20.0f, 20.0f),
        ResourceManager::GetTexture("radio"));
    Light = new GameObject(glm::vec2(220.0f, 220.0f), glm::vec2(6.0f, 12.0f),
        ResourceManager::GetTexture("radio"));
    Bass = new RadioMembrane(glm::vec2(300.0f, 350.0f),6,  glm::vec2(300.0f, 400.0f), ResourceManager::GetTexture("face"));
    Membrane = new RadioMembrane(glm::vec2(300.0f, 350.0f), 5, glm::vec2(300.0f, 400.0f), ResourceManager::GetTexture("face"));

}

void Game::Update(float dt)
{
 


}

void Game::ProcessInput(float dt)
{

}

void Game::Render(GLFWwindow* window)
{
    Radio->Draw(*Renderer);
    ResourceManager::GetShader("light").Use();
    ResourceManager::GetShader("light").SetFloat("time", glfwGetTime());
    ResourceManager::GetShader("light").SetBool("isOn", PowerOffButton->MusicPlaying);

    Light->Draw(*LightRenderer);
    PowerOffButton->Draw(*ButtonRenderer);
    glfwSetWindowUserPointer(window, PowerOffButton);
    ResourceManager::GetShader("basic").Use();
    ResourceManager::GetShader("basic").SetVector3f("uColor", PowerOffButton->Color);

    glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        PowerButton* powerOffButton = static_cast<PowerButton*>(glfwGetWindowUserPointer(window));
        powerOffButton->mouse_callback(window, button, action, mods);
        });
    Membrane->MusicPlaying = PowerOffButton->MusicPlaying;
    Bass->MusicPlaying = false;
    Bass->Draw(*CRenderer);
    Membrane->Draw(*MembraneRenderer);
}