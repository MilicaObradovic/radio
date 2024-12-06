
#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "game_object.h"
#include "radio_membrane.h"
#include "circle_renderer.h"
#include "power_off_button.h"
#include <iostream>


// Game-related State data
SpriteRenderer* Renderer;
CircleRenderer* MembraneRenderer;
CircleRenderer* LightRenderer;
SpriteRenderer* ButtonRenderer;
SpriteRenderer* AntennaRenderer;

CircleRenderer* CRenderer;
GameObject* Radio;
GameObject* Antenna;
GameObject* AntennaBase;
GameObject* AMFMbar;
GameObject* Display;
GameObject* Pointer;
GameObject* Slider;
GameObject* SliderPointer;
GameObject* ProgressBar;
GameObject* VolumeBar;


RadioMembrane* Light;
RadioMembrane* AM;
RadioMembrane* FM;

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
    delete Antenna;
    delete AntennaBase;
    delete AntennaRenderer;
    delete AMFMbar;
    delete Display;
    delete Pointer;
    delete Slider;
    delete AM;
    delete FM;
    delete SliderPointer;
    delete ProgressBar;
    delete VolumeBar;
}

void Game::Init()
{
    // load shaders
    ResourceManager::LoadShader("sprite.vs", "sprite.frag", nullptr, "sprite");
    ResourceManager::LoadShader("basic.vs", "basic.frag", nullptr, "basic");
    ResourceManager::LoadShader("basic.vs", "light.frag", nullptr, "light");
    ResourceManager::LoadShader("basic.vs", "membrane.frag", nullptr, "membrane");
    ResourceManager::LoadShader("basic.vs", "antenna.frag", nullptr, "antenna");


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
    ResourceManager::GetShader("antenna").Use();
    ResourceManager::GetShader("antenna").SetMatrix4("projection", projection);

    Shader shader = ResourceManager::GetShader("sprite");
    Shader basicShader = ResourceManager::GetShader("basic");
    Shader lightShader = ResourceManager::GetShader("light");
    Shader membraneShader = ResourceManager::GetShader("membrane");
    Shader antennaShader = ResourceManager::GetShader("antenna");

    Renderer = new SpriteRenderer(shader);
    LightRenderer = new CircleRenderer(lightShader);
    CRenderer = new CircleRenderer(basicShader);
    ButtonRenderer = new SpriteRenderer(basicShader);
    MembraneRenderer = new CircleRenderer(membraneShader);
    AntennaRenderer = new SpriteRenderer(antennaShader);


    // load textures
    ResourceManager::LoadTexture("wood3.jpg", true, "radio");
    ResourceManager::LoadTexture("awesomeface.png", true, "face");
    ResourceManager::LoadTexture("amfm3.jpg", true, "amfmscale");


    Radio = new GameObject(glm::vec2(200.0f, 200.0f), glm::vec2(350.0f, 450.0f),
        ResourceManager::GetTexture("radio"));
    PowerOffButton = new PowerButton(glm::vec2(670.0f, 210.0f), glm::vec2(20.0f, 20.0f),
        ResourceManager::GetTexture("radio"));
    Light = new RadioMembrane(glm::vec2(220.0f, 220.0f), 1, ResourceManager::GetTexture("radio"));
    AM = new RadioMembrane(glm::vec2(650.0f, 440.0f), 2, ResourceManager::GetTexture("radio"));
    FM = new RadioMembrane(glm::vec2(680.0f, 440.0f), 2, ResourceManager::GetTexture("radio"));
    Bass = new RadioMembrane(glm::vec2(310.0f, 360.0f),16, ResourceManager::GetTexture("face"));
    Membrane = new RadioMembrane(glm::vec2(310.0f, 360.0f), 14, ResourceManager::GetTexture("face"));
    Antenna = new GameObject(glm::vec2(650.0f, 250.0f), glm::vec2(300.0f, 7.0f),
        ResourceManager::GetTexture("radio"));
    AntennaBase = new GameObject(glm::vec2(650.0f, 255.0f), glm::vec2(130.0f, 17.0f),
        ResourceManager::GetTexture("radio"));

    AMFMbar = new GameObject(glm::vec2(410.0f, 340.0f), glm::vec2(200.0f, 110.0f),
        ResourceManager::GetTexture("amfmscale"));
    Display = new GameObject(glm::vec2(410.0f, 300.0f), glm::vec2(200.0f, 40.0f),
        ResourceManager::GetTexture("amfmscale"), glm::vec3(0.0f, 0.0f, 0.0f));
    ProgressBar = new GameObject(glm::vec2(360.0f, 230.0f), glm::vec2(120.0f, 40.0f),
        ResourceManager::GetTexture("amfmscale"), glm::vec3(0.0f, 0.0f, 0.0f));
    Pointer = new GameObject(glm::vec2(435.0f, 400.0f), glm::vec2(30.0f, 3.0f),
        ResourceManager::GetTexture("radio"), glm::vec3(0.7, 0.1, 0.1));
    Slider = new GameObject(glm::vec2(360.0f, 470.0f), glm::vec2(195.0f, 15.0f),
        ResourceManager::GetTexture("amfmscale"), glm::vec3(0.0f, 0.0f, 0.0f));
    SliderPointer = new GameObject(glm::vec2(370.0f, 467.0f), glm::vec2(15.0f, 21.0f),
        ResourceManager::GetTexture("amfmscale"), glm::vec3(0.7, 0.1, 0.1));
    VolumeBar = new GameObject(glm::vec2(375.0f, 237.0f), glm::vec2(0.0f, 20.0f),
        ResourceManager::GetTexture("amfmscale"), glm::vec3(0.643, 0.529, 0.475));


    AM->Color = glm::vec3(0.7, 0.1, 0.1);

}

void Game::Update(float dt){}

void Game::ProcessInput(float dt){}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << "Scroll Offset - X: " << xoffset << ", Y: " << yoffset << std::endl;

    // For example, zoom in/out based on the yoffset (vertical scroll direction)
    if (yoffset > 0) {
        std::cout << "Zooming In" << std::endl;
        Pointer->Position.x += 3;
        if (Pointer->Position.x > 690.0f) {
            Pointer->Position.x = 690.0f;
        }
    }else if (yoffset < 0) {
        std::cout << "Zooming Out" << std::endl;
        Pointer->Position.x -= 3;
        if (Pointer->Position.x < 435.0f) {
            Pointer->Position.x = 435.0f;
        }
    }
}

bool isDragging = false;
float mouseOffset = 0;
// Mouse position callback
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (isDragging) {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        if (xpos < SliderPointer->Position.x ) {
            SliderPointer->Position.x -= 5;
            VolumeBar->Size.x -= 2;
            Membrane->Velocity -= 0.001;
        }else if (xpos > SliderPointer->Position.x) {
            SliderPointer->Position.x += 5;
            VolumeBar->Size.x += 2;
            Membrane->Velocity += 0.001;
        }

        if (SliderPointer->Position.x < 370) {
            SliderPointer->Position.x = 370;
            VolumeBar->Size.x = 0;
            Membrane->Velocity = 0;

        }
        else if(SliderPointer->Position.x > 620) {
            SliderPointer->Position.x = 620;
            VolumeBar->Size.x = 100;
            Membrane->Velocity = 0.05;

        }
    }
}

// Mouse button callback
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            glm::vec2 mousePos(xpos, ypos);
            int width, height;
            glfwGetWindowSize(window, &width, &height);

            if (xpos >= SliderPointer->Position.x && xpos <= SliderPointer->Position.x + 1.5 * SliderPointer->Size.x &&
                ypos >= SliderPointer->Position.y && ypos <= SliderPointer->Position.y + SliderPointer->Size.y) {
                std::cout << "Click" << std::endl;

                isDragging = true;
                mouseOffset = xpos - SliderPointer->Position.x;
            }
            if (xpos >= PowerOffButton->Position.x && xpos <= PowerOffButton->Position.x + 1.5 * PowerOffButton->Size.x &&
                ypos >= PowerOffButton->Position.y && ypos <= PowerOffButton->Position.y + PowerOffButton->Size.y) {
                std::cout << "Power" << std::endl;

                PowerOffButton->MusicPlaying = !PowerOffButton->MusicPlaying;

                if (!PowerOffButton->MusicPlaying) {
                    PowerOffButton->Color = glm::vec3(0.7, 0.1, 0.1);
                }
                else {
                    PowerOffButton->Color = glm::vec3(0.0f);
                }
            }
        }
        else if (action == GLFW_RELEASE) {
            isDragging = false;
        }
    }
}

void Game::Render(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        Antenna->Size = glm::vec2(160.0f, 7.0f);
    }else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        Antenna->Size = glm::vec2(300.0f, 7.0f);
    }else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        AM->Color = glm::vec3(0.7, 0.1, 0.1);
        FM->Color = glm::vec3(0.0, 0.0, 0.0);

    }else if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        FM->Color = glm::vec3(0.7, 0.1, 0.1);
        AM->Color = glm::vec3(0.0, 0.0, 0.0);

    }
    Antenna->Draw(*AntennaRenderer, true, false);
    AntennaBase->Draw(*AntennaRenderer, true, false);

    Radio->Draw(*Renderer, false, false);
    ResourceManager::GetShader("light").Use();
    ResourceManager::GetShader("light").SetFloat("time", glfwGetTime());
    ResourceManager::GetShader("light").SetBool("isOn", PowerOffButton->MusicPlaying);
    Light->MusicPlaying = false;
    Light->Draw(*LightRenderer);
    PowerOffButton->Draw(*ButtonRenderer, false, false);
    glfwSetWindowUserPointer(window, PowerOffButton);
    ResourceManager::GetShader("basic").Use();
    ResourceManager::GetShader("basic").SetVector3f("uColor", PowerOffButton->Color);

    /*glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
        PowerButton* powerOffButton = static_cast<PowerButton*>(glfwGetWindowUserPointer(window));
        powerOffButton->mouse_callback(window, button, action, mods);
        });*/
    glfwSetScrollCallback(window, scroll_callback);

    Membrane->MusicPlaying = PowerOffButton->MusicPlaying;
    Bass->MusicPlaying = false;
    Bass->Draw(*CRenderer);
    Membrane->Draw(*MembraneRenderer);
    AMFMbar->Draw(*Renderer, false, false);
    Display->Draw(*ButtonRenderer, false, false);
    Pointer->Draw(*ButtonRenderer, false, true);
    Slider->Draw(*ButtonRenderer, false, false);
    AM->MusicPlaying = false;
    AM->Draw(*CRenderer);
    FM->MusicPlaying = false;
    FM->Draw(*CRenderer);
    SliderPointer->Draw(*ButtonRenderer, false, false);
    ProgressBar->Draw(*ButtonRenderer, false, false);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    VolumeBar->Draw(*ButtonRenderer, false, false);


}

