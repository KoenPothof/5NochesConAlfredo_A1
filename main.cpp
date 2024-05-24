#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenCv.h"

#include "GameObject.h"
#include "DrawComponent.h"
#include "RectangleComponent.h"
#include "RoomComponent.h"
#include "DebugComponent.h"
#include "CameraComponent.h"

#include "Texture.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
OpenCv openCv;

std::shared_ptr<GameObject> debugPlayer;
std::shared_ptr<GameObject> object3;
Texture texture = Texture("assets/spritesheet.png", 4736, 128, 128);



void init();
void update();
void draw();
void runOpencv();
glm::mat4 getDebugMatrix();
glm::mat4 getMatrix();

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1400, 800, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Could not initialize glwf";
    }
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK)
    {
        throw "Could not initialize GLEW";
    }
    tigl::init();

    init();

    while (!glfwWindowShouldClose(window))
    {
        update();
        draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
  
    glfwTerminate();

    return 0;
}

std::list<std::shared_ptr<GameObject>> gameObjects;

void init()
{
    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });

    openCv = OpenCv();

    auto roomObject = std::make_shared<GameObject>();
    roomObject->position = glm::vec3(0, 0, 0);
    auto roomComponent = std::make_shared<RoomComponent>(20, 30, 10); // Example dimensions
    roomObject->addComponent(roomComponent);
    gameObjects.push_back(roomObject);

   /* auto rectangleObject = std::make_shared<GameObject>();
    rectangleObject->position = glm::vec3(0, 0, 5);
    auto rectangleComponent = std::make_shared<RectangleComponent>(0, false, 10, 5);
    rectangleObject->addComponent(rectangleComponent);
    gameObjects.push_back(rectangleObject);*/

    // Create and add DebugComponent
    debugPlayer = std::make_shared<GameObject>();
    auto debugComponent = std::make_shared<DebugComponent>();
    debugPlayer->addComponent(debugComponent);
    debugPlayer->position = glm::vec3(0, 2, 0);
    gameObjects.push_back(debugPlayer);
}

void update()
{
    double currentTime = glfwGetTime();
    static double lastTime = currentTime;
    float deltaTime = float(currentTime - lastTime);
    lastTime = currentTime;

    //runOpencv();

    for (auto& go : gameObjects)
        go->update(deltaTime);

}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

    tigl::shader->setProjectionMatrix(projection);
    tigl::shader->setViewMatrix(getDebugMatrix());

    tigl::shader->setModelMatrix(glm::mat4(1.0f));
    tigl::shader->enableTexture(true);

    for (auto& go : gameObjects)
        go->draw();
}

void runOpencv()
{
    openCv.run();
}

glm::mat4 getDebugMatrix()
{
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::rotate(viewMatrix, debugPlayer->rotation.x, glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, debugPlayer->rotation.y, glm::vec3(0, 1, 0));
    viewMatrix = glm::translate(viewMatrix, -debugPlayer->position);
    return viewMatrix;
}


glm::mat4 getMatrix()
{
    glm::mat4 view(1.0f);
    view = glm::rotate(view, object3->rotation.x, glm::vec3(1, 0, 0));
    view = glm::rotate(view, object3->rotation.y, glm::vec3(0, 1, 0));
    view = glm::translate(view, -object3->position);
    return view;
}

