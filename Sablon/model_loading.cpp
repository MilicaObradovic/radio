#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "filesystem.h"
#include "shader_m.h"
#include "camera.h"
#include "model.h"

#include <iostream>
#include <direct.h>  // for _getcwd
#include <cstdlib>
#include "game_object.h"
#include "resource_manager.h"
#include <ctime>
#include "text_renderer.h"
#include <chrono>
#include <thread>
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
bool orthogonal = false;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
// GLFW function declarations


// The Width of the screen
const unsigned int SCREEN_WIDTH = 950;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;
TextRenderer* TextBig;
int main()
{
    
    srand(static_cast<unsigned int>(time(nullptr)));

    if (!glfwInit()) // !0 == 1; glfwInit inicijalizuje GLFW i vrati 1 ako je inicijalizovana uspjesno, a 0 ako nije
    {
        std::cout << "GLFW Biblioteka se nije ucitala! :(\n";
        return 1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, false);

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Radio", nullptr, nullptr);


    if (window == NULL) //Ako prozor nije napravljen
    {
        std::cout << "Prozor nije napravljen! :(\n";
        glfwTerminate(); //Gasi GLFW
        return 2; //Vrati kod za gresku
    }
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    // Inicijalizacija GLEW biblioteke
    if (glewInit() != GLEW_OK) //Slicno kao glfwInit. GLEW_OK je predefinisani izlazni kod za uspjesnu inicijalizaciju sadrzan unutar biblioteke
    {
        std::cout << "GLEW nije mogao da se ucita! :'(\n";
        return 3;
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);


    // build and compile shaders
    // -------------------------
    TextBig = new TextRenderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    TextBig->Load("LiberationSans-Regular.ttf", 22);
    Shader2 ourShader("model_loading.vs", "model_loading.frag");
    ResourceManager::LoadShader("sprite.vs", "sprite.frag", nullptr, "platform");

    Shader shader = ResourceManager::GetShader("platform");

    SpriteRenderer* Renderer = new SpriteRenderer(shader);
    // load models

    Model* models[4];
  
    models[0]= new  Model(glm::vec3(-45.0f, -10.0f, 0.0f), FileSystem::getPath("cube/CubiCubeRed.obj"));
    models[1] = new  Model(glm::vec3(-45.0f, -5.0f, 0.0f), FileSystem::getPath("cube/CubiCubeRed.obj"));
    models[2] = new  Model(glm::vec3(-45.0f, 0.0f, 0.0f), FileSystem::getPath("cube/CubiCubeRed.obj"));
    models[3] = new  Model(glm::vec3(-45.0f, 5.0f, 0.0f), FileSystem::getPath("cube/CubiCubeRed.obj"));
    GameObject* Platform = new GameObject(glm::vec2(50.0f, 0.0f), glm::vec2(500.0f, 500.0f), ResourceManager::GetTexture("radio"));

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    float i = 0;
    while (!glfwWindowShouldClose(window))
    {
        float startTime = glfwGetTime();
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // don't forget to enable shader before setting uniforms
        ourShader.use();

        // view/projection transformations
        glm::mat4 projection;
        float aspect = (float)SCR_WIDTH / (float)SCR_HEIGHT;

        if (!orthogonal) {
            projection = glm::perspective(glm::radians(camera.Zoom), aspect, 0.1f, 200.0f);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else {
            float orthoScale = 50.0f;
            projection = glm::ortho(-orthoScale * aspect, orthoScale * aspect,
                -orthoScale, orthoScale,
                0.1f, 100.0f);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            camera.ResetCameraPosition();
        }
        
        glm::mat4 view = camera.GetViewRadiusCamera();
        glm::vec3 color(1.0f, 0.0f, 0.0f);

        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        ourShader.setVec3("objectColor", 1.0f, 1.0f, 0.0f);
        float time = glfwGetTime();

        float angle = time * 500.0f;
        
        for (int i = 0; i < 4; i++) {
            if ((*models[i]).position.x >= 51) {
                for (int i = 0; i < 4; i++) {
                    (*models[i]).Stop();
                }
                break;
            }
        }
        (*models[0]).Draw(ourShader, glm::vec3(1.0f, 0.0f, 0.0f), angle);
        (*models[1]).Draw(ourShader, glm::vec3(1.0f, 1.0f, 0.0f), angle);
        (*models[2]).Draw(ourShader, glm::vec3(0.0f, 0.0f, 1.0f), angle);
        (*models[3]).Draw(ourShader, glm::vec3(0.0f, 1.0f, 0.0f), angle);
        ResourceManager::GetShader("platform").Use();
        ResourceManager::GetShader("platform").SetMatrix4("projection", projection);
        ResourceManager::GetShader("platform").SetMatrix4("view", view);

        Platform->Draw(*Renderer, false, false);

        TextBig->RenderText("Milica Obradovic SV40/2021", 5.0f, 5.0f, 1.0f, glm::vec3(0.643, 0.529, 0.475));

       

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
        float endTime = glfwGetTime();
        float delta = (startTime - endTime)*1000;
        if (delta < 1000 / 60) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000/60 - int(delta)));
        }
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    delete Platform;
    delete TextBig;
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) 
         glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);         
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    if (!orthogonal) {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            camera.ProcessKeyboard(FORWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            camera.ProcessKeyboard(LEFT, deltaTime);
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            camera.ProcessKeyboard(RIGHT, deltaTime);
    }
    
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if (orthogonal) {

    }
    else {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera.ProcessMouseMovement(xoffset, yoffset);
    }
    
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (key == GLFW_KEY_P && action == GLFW_PRESS)
    {
        orthogonal = !orthogonal;
        std::cout << (orthogonal ? "Switched to Perspective" : "Switched to Orthographic") << std::endl;
    } 
    if (key >= 0 && key < 1024) 
    {
        
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}