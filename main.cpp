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

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
OpenCv openCv;

std::shared_ptr<GameObject> debugPlayer;
std::shared_ptr<GameObject> object3;
Texture texture = Texture("assets/spritesheet.png", 4736, 128, 128);

float romigeKwarkTaardt = 0.0f;
bool pauseCamera = false;

void init();
void update();
void draw();
void runOpencv();
glm::mat4 currentMatrix;
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

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(nullptr);

    init();

    while (!glfwWindowShouldClose(window))
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        update();
        draw();

        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(0, 400));
            ImGui::Begin("Demo Selection");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::BeginGroup();
            ImGui::SliderFloat("Romige kwarkTaardt", &romigeKwarkTaardt, -10, 10);
            ImGui::EndGroup();

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

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
            if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
            {
                pauseCamera = !pauseCamera;

                if (pauseCamera)
                {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                }
                else
                {
                    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
            }

            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });

    glEnable(GL_DEPTH_TEST);

    //openCv = OpenCv();

    auto roomObjectA = std::make_shared<GameObject>();
    roomObjectA->position = glm::vec3(0, 0, 0);
    auto roomComponentA = std::make_shared<RoomComponent>(10, 10); // Example dimensions
    roomObjectA->addComponent(roomComponentA);
    gameObjects.push_back(roomObjectA);

    auto roomObjectB = std::make_shared<GameObject>();
    roomObjectB->position = glm::vec3(10, 0, 0);
    auto roomComponentB = std::make_shared<RoomComponent>(10, 10); // Example dimensions
    roomObjectB->addComponent(roomComponentB);
    gameObjects.push_back(roomObjectB);

    auto roomObjectC = std::make_shared<GameObject>();
    roomObjectC->position = glm::vec3(10, 0, -15);
    auto roomComponentC = std::make_shared<RoomComponent>(20, 20); // Example dimensions
    roomObjectC->addComponent(roomComponentC);
    gameObjects.push_back(roomObjectC);

    auto roomObjectD = std::make_shared<GameObject>();
    roomObjectD->position = glm::vec3(25, 0, -25);
    auto roomComponentD = std::make_shared<RoomComponent>(15, 15); // Example dimensions
    roomObjectD->addComponent(roomComponentD);
    gameObjects.push_back(roomObjectD);

    auto roomObjectE = std::make_shared<GameObject>();
    roomObjectE->position = glm::vec3(40, 0, -25);
    auto roomComponentE = std::make_shared<RoomComponent>(15, 15); // Example dimensions
    roomObjectE->addComponent(roomComponentE);
    gameObjects.push_back(roomObjectE);

    auto roomObjectF = std::make_shared<GameObject>();
    roomObjectF->position = glm::vec3(53, 0, -5);
    auto roomComponentF = std::make_shared<RoomComponent>(20, 15); // Example dimensions
    roomObjectF->addComponent(roomComponentF);
    gameObjects.push_back(roomObjectF);

    auto roomObjectG = std::make_shared<GameObject>();
    roomObjectG->position = glm::vec3(53, 0, 10);
    auto roomComponentG = std::make_shared<RoomComponent>(20, 15); // Example dimensions
    roomObjectG->addComponent(roomComponentG);
    gameObjects.push_back(roomObjectG);

    auto roomObjectH = std::make_shared<GameObject>();
    roomObjectH->position = glm::vec3(40, 0, 25);
    auto roomComponentH = std::make_shared<RoomComponent>(15, 15); // Example dimensions
    roomObjectH->addComponent(roomComponentH);
    gameObjects.push_back(roomObjectH);

    auto roomObjectI = std::make_shared<GameObject>();
    roomObjectI->position = glm::vec3(25, 0, 25);
    auto roomComponentI = std::make_shared<RoomComponent>(15, 15); // Example dimensions
    roomObjectI->addComponent(roomComponentI);
    gameObjects.push_back(roomObjectI);

    auto roomObjectJ = std::make_shared<GameObject>();
    roomObjectJ->position = glm::vec3(10, 0, 25);
    auto roomComponentJ = std::make_shared<RoomComponent>(20, 20); // Example dimensions
    roomObjectJ->addComponent(roomComponentJ);
    gameObjects.push_back(roomObjectJ);

    auto roomObjectK = std::make_shared<GameObject>();
    roomObjectK->position = glm::vec3(38, 0, 10);
    auto roomComponentK = std::make_shared<RoomComponent>(35, 28); // Example dimensions
    roomObjectK->addComponent(roomComponentK);
    gameObjects.push_back(roomObjectK);

    auto roomObjectHallWayRight = std::make_shared<GameObject>();
    roomObjectHallWayRight->position = glm::vec3(10, 0, 5);
    auto roomComponentHallWayRight = std::make_shared<RoomComponent>(5, 20); // Example dimensions
    roomObjectHallWayRight->addComponent(roomComponentHallWayRight);
    gameObjects.push_back(roomObjectHallWayRight);

    auto roomObjectHallWayLeft = std::make_shared<GameObject>();
    roomObjectHallWayLeft->position = glm::vec3(10, 0, -10);
    auto roomComponentHallWayLeft = std::make_shared<RoomComponent>(5, 20); // Example dimensions
    roomObjectHallWayLeft->addComponent(roomComponentHallWayLeft);
    gameObjects.push_back(roomObjectHallWayLeft);



    

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

    texture.bind();

    object3 = std::make_shared<GameObject>();
    object3->position = glm::vec3(0, 0, 0);
    object3->addComponent(std::make_shared<CameraComponent>(1.0f, 1.0f));
    gameObjects.push_back(object3);

    openCv.init();
}

void update()
{
    double currentTime = glfwGetTime();
    static double lastTime = currentTime;
    float deltaTime = float(currentTime - lastTime);
    lastTime = currentTime;

    runOpencv();

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

    if (pauseCamera)
        tigl::shader->setViewMatrix(currentMatrix);
    else
        tigl::shader->setViewMatrix(getMatrix());

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
    currentMatrix = viewMatrix;
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

