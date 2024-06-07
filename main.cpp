#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "VisionComponent.h"

#include "GameObject.h"
#include "DrawComponent.h"
#include "RectangleComponent.h"
#include "RoomComponent.h"
#include "DebugComponent.h"
#include "CameraComponent.h"
#include "ModelComponent.h"
#include "EnemyComponent.h"
#include "SecurityDoorComponent.h"
#include "GameManager.h"
#include "TextComponent.h"

#include "Texture.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

std::shared_ptr<GameObject> debugPlayer;
std::shared_ptr<GameObject> object3;
std::shared_ptr<GameObject> enemy;
std::shared_ptr<GameObject> securityDoor, securityDoor1;
std::shared_ptr<GameManager> gameManager;
Texture texture = Texture("assets/spritesheet.png", 4736, 128, 128);
std::string enumConverter[13] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "HALL_LEFT", "HALL_RIGHT"};
const std::string ALFREDO_PATH = "assets/models/haribo/haribo.obj";
const std::string ENEMY_PATH = "assets/models/eng_beest_ahhhh/eng_beest_ahhh.obj";

float romigeKwarkTaardt = 0.0f;
bool pauseCamera = false;

void init();
void update();
void draw();
void runOpencv();
void initRoom();
glm::mat4 currentMatrix;
glm::mat4 getDebugMatrix();
glm::mat4 getMatrix();

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1800, 1000, "Hello World", NULL, NULL);
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
            ImGui::Text("Player position: x: %.3f, y: %.3f, z: %.3f", debugPlayer->position.x, debugPlayer->position.y, debugPlayer->position.z);
            ImGui::Text("Player rotation: x: %.3f, y: %.3f, z: %.3f", debugPlayer->rotation.x, debugPlayer->rotation.y, debugPlayer->rotation.z);         

            ImGui::BeginGroup();
            ImGui::SliderFloat("Romige kwarkTaardt", &romigeKwarkTaardt, -10, 10);
            ImGui::SliderFloat("Beest pos x", &enemy->position.x, -15.0f, 15.0f);
            ImGui::SliderFloat("Beest pos y", &enemy->position.y, -15.0f, 15.0f);
            ImGui::SliderFloat("Beest pos z", &enemy->position.z, -15.0f, 15.0f);
            ImGui::SliderFloat("Beest rot x", &enemy->rotation.x, -3.14f, 3.14f);
            ImGui::SliderFloat("Beest rot y", &enemy->rotation.y, -3.14f, 3.14f);
            ImGui::SliderFloat("Beest rot z", &enemy->rotation.z, -3.14f, 3.14f);
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

            if (key == GLFW_KEY_R && action == GLFW_PRESS)
            {
				enemy->getComponent<EnemyComponent>()->moveToNextRoom();
			}

            if (key == GLFW_KEY_T && action == GLFW_PRESS)
            {
				securityDoor->getComponent<SecurityDoorComponent>()->isClosed = !securityDoor->getComponent<SecurityDoorComponent>()->isClosed;
			}

            if (key == GLFW_KEY_Y && action == GLFW_PRESS)
            {
                securityDoor1->getComponent<SecurityDoorComponent>()->isClosed = !securityDoor1->getComponent<SecurityDoorComponent>()->isClosed;
            }

            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);
        });

    glEnable(GL_DEPTH_TEST);

    //openCv = OpenCv();
    gameManager = std::make_shared<GameManager>();
    initRoom();


    enemy = std::make_shared<GameObject>(gameManager);
    enemy->addComponent(std::make_shared<ModelComponent>(ENEMY_PATH));
    std::vector<EnemyComponent::EnemyLocations> enemyPath = { EnemyComponent::F, EnemyComponent::K, EnemyComponent::D, EnemyComponent::C, EnemyComponent::HALL_LEFT, EnemyComponent::A};
    std::vector<glm::vec3> positions = 
    { 
        glm::vec3(47.248f, -1.162f, -15.329f),
        glm::vec3(30.787f, -1.162f, -16.759f),
        glm::vec3(18.546f, -1.162f, -32.304f),
        glm::vec3(6.3f, -3.558f, -21.506f),
        glm::vec3(-7.272f, -2.744f, -13.600f)
    };
    std::vector<glm::vec3> rotations =
    {
        glm::vec3(-0.040f, 2.964f, 0),
        glm::vec3(0.003f, 3.774f, 0),
        glm::vec3(0.694f, 4.287f, 0.790f),
        glm::vec3(0.227f, 5.336f, 0),
        glm::vec3(0.040f, 0.358f, 0)
    };
    enemy->position = glm::vec3(0, -1.0f, 0);
    enemy->scale = glm::vec3(80.1f, 80.1f, 80.1f);
    enemy->addComponent(std::make_shared<EnemyComponent>(enemyPath, positions, rotations));
    enemy->getComponent<EnemyComponent>()->init();
    gameManager->enemy = enemy;
    gameObjects.push_back(enemy);

    // Create and add DebugComponent
    debugPlayer = std::make_shared<GameObject>(gameManager);
    auto debugComponent = std::make_shared<DebugComponent>();
    auto fontComponent = std::make_shared<TextComponent>();
    debugPlayer->addComponent(debugComponent);
    debugPlayer->addComponent(fontComponent);
    debugPlayer->position = glm::vec3(0, 2, 0);
    gameObjects.push_back(debugPlayer);

    // Create and add object3
    //object3 = std::make_shared<GameObject>();
    //object3->position = glm::vec3(0, 2, 0);
    //object3->addComponent(std::make_shared<CameraComponent>(1.0f, 1.0f));
    //object3->addComponent(std::make_shared<VisionComponent>());
    //gameObjects.push_back(object3);
    //
    //object3->getComponent<VisionComponent>()->init();

    texture.bind();
}

void update()
{
    double currentTime = glfwGetTime();
    static double lastTime = currentTime;
    float deltaTime = float(currentTime - lastTime);
    lastTime = currentTime;
	gameManager->update(deltaTime);


    //runOpencv();
    glEnable(GL_DEPTH_TEST);

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
        tigl::shader->setViewMatrix(getDebugMatrix());

    tigl::shader->setModelMatrix(glm::mat4(1.0f));
    tigl::shader->enableTexture(true);

    for (auto& go : gameObjects)
        go->draw();
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

void initRoom()
{
    auto roomObjectA = std::make_shared<GameObject>();
    roomObjectA->position = glm::vec3(0, 0, 0);
    auto roomComponentA = std::make_shared<RoomComponent>(10, 10, 2, RoomComponent::FRONTBACK); // Example dimensions
    roomObjectA->addComponent(roomComponentA);
    gameObjects.push_back(roomObjectA);

    auto roomObjectB = std::make_shared<GameObject>();
    roomObjectB->position = glm::vec3(10, 0, 0);
    auto roomComponentB = std::make_shared<RoomComponent>(10, 10, 3, RoomComponent::BACK); // Example dimensions
    roomObjectB->addComponent(roomComponentB);
    gameObjects.push_back(roomObjectB);

    auto roomObjectC = std::make_shared<GameObject>();
    roomObjectC->position = glm::vec3(10, 0, -15);
    auto roomComponentC = std::make_shared<RoomComponent>(20, 20, 3, RoomComponent::FRONT); // Example dimensions
    roomObjectC->addComponent(roomComponentC);
    gameObjects.push_back(roomObjectC);

    auto roomObjectD = std::make_shared<GameObject>();
    roomObjectD->position = glm::vec3(25, 0, -25);
    auto roomComponentD = std::make_shared<RoomComponent>(15, 15, 3, RoomComponent::FRONT); // Example dimensions
    roomObjectD->addComponent(roomComponentD);
    gameObjects.push_back(roomObjectD);

    auto roomObjectE = std::make_shared<GameObject>();
    roomObjectE->position = glm::vec3(40, 0, -25);
    auto roomComponentE = std::make_shared<RoomComponent>(15, 15, 3, RoomComponent::FRONT); // Example dimensions
    roomObjectE->addComponent(roomComponentE);
    gameObjects.push_back(roomObjectE);

    auto roomObjectF = std::make_shared<GameObject>();
    roomObjectF->position = glm::vec3(53, 0, -5);
    auto roomComponentF = std::make_shared<RoomComponent>(20, 15, 3, RoomComponent::STAGE); // Example dimensions
    roomObjectF->addComponent(roomComponentF);
    gameObjects.push_back(roomObjectF);

    auto roomObjectG = std::make_shared<GameObject>();
    roomObjectG->position = glm::vec3(53, 0, 10);
    auto roomComponentG = std::make_shared<RoomComponent>(20, 15, 5, RoomComponent::LEFT); // Example dimensions
    roomObjectG->addComponent(roomComponentG);
    gameObjects.push_back(roomObjectG);

    auto roomObjectH = std::make_shared<GameObject>();
    roomObjectH->position = glm::vec3(40, 0, 25);
    auto roomComponentH = std::make_shared<RoomComponent>(15, 15, 3, RoomComponent::BACK); // Example dimensions
    roomObjectH->addComponent(roomComponentH);
    gameObjects.push_back(roomObjectH);

    auto roomObjectI = std::make_shared<GameObject>();
    roomObjectI->position = glm::vec3(25, 0, 25);
    auto roomComponentI = std::make_shared<RoomComponent>(15, 15, 1, RoomComponent::BACK); // Example dimensions
    roomObjectI->addComponent(roomComponentI);
    gameObjects.push_back(roomObjectI);

    auto roomObjectJ = std::make_shared<GameObject>();
    roomObjectJ->position = glm::vec3(10, 0, 25);
    auto roomComponentJ = std::make_shared<RoomComponent>(20, 20, 1, RoomComponent::BACK); // Example dimensions
    roomObjectJ->addComponent(roomComponentJ);
    gameObjects.push_back(roomObjectJ);

    auto roomObjectK = std::make_shared<GameObject>();
    roomObjectK->position = glm::vec3(38, 0, 10);
    auto roomComponentK = std::make_shared<RoomComponent>(35, 28, 1, RoomComponent::MAINROOM); // Example dimensions
    roomObjectK->addComponent(roomComponentK);
    gameObjects.push_back(roomObjectK);

    auto roomObjectHallWayRight = std::make_shared<GameObject>();
    roomObjectHallWayRight->position = glm::vec3(10, 0, 5);
    auto roomComponentHallWayRight = std::make_shared<RoomComponent>(5, 20, 1, RoomComponent::HALLWAY); // Example dimensions
    roomObjectHallWayRight->addComponent(roomComponentHallWayRight);
    gameObjects.push_back(roomObjectHallWayRight);

    auto roomObjectHallWayLeft = std::make_shared<GameObject>();
    roomObjectHallWayLeft->position = glm::vec3(10, 0, -10);
    auto roomComponentHallWayLeft = std::make_shared<RoomComponent>(5, 20, 3, RoomComponent::HALLWAY); // Example dimensions
    roomObjectHallWayLeft->addComponent(roomComponentHallWayLeft);
    gameObjects.push_back(roomObjectHallWayLeft);

    securityDoor = std::make_shared<GameObject>(gameManager);
    securityDoor->position = glm::vec3(-6.640f, 0, 0.316f);
    securityDoor->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 0, false, 5, 7, texture.setTexture(6, 0), 0));
    securityDoor->addComponent(std::make_shared<SecurityDoorComponent>());
    gameManager->rightDoor = securityDoor;
    gameObjects.push_back(securityDoor);

    securityDoor1 = std::make_shared<GameObject>(gameManager);
    securityDoor1->position = glm::vec3(-6.640f, 0, -9.486f);
    securityDoor1->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 0, false, 5, 7, texture.setTexture(6, 0), 0));
    securityDoor1->addComponent(std::make_shared<SecurityDoorComponent>());
    gameManager->leftDoor = securityDoor1;
    gameObjects.push_back(securityDoor1);
}

