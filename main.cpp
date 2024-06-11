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
#include "SecurityCameraComponent.h"
#include "ScreenComponent.h"
#include "ModelComponent.h"
#include "EnemyComponent.h"
#include "SecurityDoorComponent.h"
#include "DoubleTextComponent.h"
#include "CameraSystemToggleComponent.h"
#include "RunningEnemyComponent.h"

#include "Texture.h"
#include "fbo.h"
#include "GameManager.h"
#include "TextComponent.h"
#include "LightComponent.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;

std::shared_ptr<Fbo> fbo;
std::shared_ptr<GameObject> debugPlayer;
std::shared_ptr<GameObject> object3;
std::shared_ptr<GameObject> camera;
std::shared_ptr<GameObject> enemy1, enemy2, enemy3, runningEnemy;
std::shared_ptr<GameObject> securityDoor, securityDoor1;
std::shared_ptr<GameManager> gameManager;
std::shared_ptr<GameObject> light;
std::shared_ptr<GameObject> cameraSystemToggler;

Texture* texture;
Texture* textureFloor;
Texture* textureWall;
Texture* textureCeiling;
Texture* textureDoor;
Texture* textureMap;
Texture* textureCameraOff;

std::string enumConverter[13] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "HALL_LEFT", "HALL_RIGHT"};
const std::string ALFREDO_PATH = "assets/models/haribo/haribo.obj";

const std::string ENEMY_PATH1 = "assets/models/kai_beest/kai_beest.obj";
const std::string ENEMY_PATH2 = "assets/models/freaky_ahh_beest/monster.obj";
const std::string ENEMY_PATH3 = "assets/models/sklt/sklt.obj";

bool pauseCamera = false;
int selectedCamera = 1;

void init();
void update();
void buildFbo();
void draw();
void runOpencv();
void initRoom();
void initSecurity();
glm::mat4 currentMatrix;
glm::mat4 getDebugMatrix();
glm::mat4 getMatrix();

int main(void)
{
    if (!glfwInit())
        throw "Could not initialize glwf";
    window = glfwCreateWindow(1920, 1080, "5NochesConAlfredo", NULL, NULL);
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
        buildFbo();
        draw();

        {
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            ImGui::SetNextWindowSize(ImVec2(0, 400));
            ImGui::Begin("Demo Selection");
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::Text("Player position: x: %.3f, y: %.3f, z: %.3f", debugPlayer->position.x, debugPlayer->position.y, debugPlayer->position.z);
            ImGui::Text("Player rotation: x: %.3f, y: %.3f, z: %.3f", debugPlayer->rotation.x, debugPlayer->rotation.y, debugPlayer->rotation.z);

            ImGui::BeginGroup();
            ImGui::SliderInt("Selected Camera", &selectedCamera, 1, 10);
            ImGui::Checkbox("Beest staat stil", &enemy2->getComponent<EnemyComponent>()->isFrozen);
            ImGui::Text("Beest voor aanval: %.3f", enemy2->getComponent<EnemyComponent>()->moveTime);
            ImGui::Text("Beest voor aanval: %.3f", enemy2->getComponent<EnemyComponent>()->deltaTimeEnemy);

            ImGui::Text("Beest voor aanval: %.3f", enemy3->getComponent<EnemyComponent>()->moveTime);
            ImGui::Text("Beest voor aanval: %.3f", enemy3->getComponent<EnemyComponent>()->deltaTimeEnemy);

            
            ImGui::SliderFloat("Running enemy X", &runningEnemy->position.x, -30.f, 30.f);
            ImGui::SliderFloat("Running enemy Y", &runningEnemy->position.y, -30.f, 30.f);
            ImGui::SliderFloat("Running enemy Z", &runningEnemy->position.z, -30.f, 30.f);

            ImGui::SliderFloat("Rot enemy X", &runningEnemy->rotation.x, -4.0f, 4.0f);
            ImGui::SliderFloat("Rot enemy Y", &runningEnemy->rotation.y, -4.0f, 4.0f);
            ImGui::SliderFloat("Rot enemy Z", &runningEnemy->rotation.z, -4.0f, 4.0f);

            ImGui::Checkbox("Running enemy staat stil", &runningEnemy->getComponent<RunningEnemyComponent>()->isFrozen);
            ImGui::Text("Running enemy voor aanval: %.3f", runningEnemy->getComponent<RunningEnemyComponent>()->moveTime);
            ImGui::Text("Running enemy voor aanval: %.3f", runningEnemy->getComponent<RunningEnemyComponent>()->deltaTimeEnemy);
           
      
            ImGui::SliderFloat("Light position X", &light->position.x, -10.0f, 10.0f);
            ImGui::SliderFloat("Light position Y", &light->position.y, -10.0f, 10.0f);
            ImGui::SliderFloat("Light position Z", &light->position.z, -10.0f, 10.0f);

            ImGui::SliderFloat("Light diffuse X", &light->getComponent<LightComponent>()->diffuse.x, -2.0f, 2.0f);
            ImGui::SliderFloat("Light diffuse Y", &light->getComponent<LightComponent>()->diffuse.y, -2.0f, 2.0f);
            ImGui::SliderFloat("Light diffuse Z", &light->getComponent<LightComponent>()->diffuse.z, -2.0f, 2.0f);

            ImGui::SliderFloat("Light ambient X", &light->getComponent<LightComponent>()->ambient.x, -2.0f, 2.0f);
            ImGui::SliderFloat("Light ambient Y", &light->getComponent<LightComponent>()->ambient.y, -2.0f, 2.0f);
            ImGui::SliderFloat("Light ambient Z", &light->getComponent<LightComponent>()->ambient.z, -2.0f, 2.0f);

            ImGui::SliderFloat("Light specular X", &light->getComponent<LightComponent>()->specular.x, -2.0f, 2.0f);
            ImGui::SliderFloat("Light specular Y", &light->getComponent<LightComponent>()->specular.y, -2.0f, 2.0f);
            ImGui::SliderFloat("Light specular Z", &light->getComponent<LightComponent>()->specular.z, -2.0f, 2.0f);
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
				//enemy1->getComponent<EnemyComponent>()->moveToNextRoom();
                enemy2->getComponent<EnemyComponent>()->moveToNextRoom();
                //enemy3->getComponent<EnemyComponent>()->moveToNextRoom();

			}

            if (key == GLFW_KEY_T && action == GLFW_PRESS)
            {
                gameManager->rightDoorToggle();
				//securityDoor->getComponent<SecurityDoorComponent>()->isClosed = !securityDoor->getComponent<SecurityDoorComponent>()->isClosed;
			}

            if (key == GLFW_KEY_Y && action == GLFW_PRESS)
            {
                gameManager->leftDoorToggle();
                //securityDoor1->getComponent<SecurityDoorComponent>()->isClosed = !securityDoor1->getComponent<SecurityDoorComponent>()->isClosed;
            }

            if (key == GLFW_KEY_P && action == GLFW_PRESS)
            {
                gameManager->toggleCameraSystem();
                //cameraSystemToggler->getComponent<CameraSystemToggleComponent>()->isOff = !cameraSystemToggler->getComponent<CameraSystemToggleComponent>()->isOff;
            }

            if (key == GLFW_KEY_ESCAPE)
                glfwSetWindowShouldClose(window, true);

            if (key == GLFW_KEY_Z && action == GLFW_PRESS)
            {
                selectedCamera++;
                if (selectedCamera > 10)
                {
                    selectedCamera = 1;
                }
            }
                
        });

    glEnable(GL_DEPTH_TEST);

    //openCv = OpenCv();
    fbo = std::make_shared<Fbo>(800, 600);
    texture = new Texture("assets/spritesheet.png", 4736, 128, 128);
    textureFloor = new Texture("assets/floorTexture.png", 128, 128, NULL);
    textureWall = new Texture("assets/brickWallTexture.jpg", 128, 128, NULL);
    textureCeiling = new Texture("assets/ceiling.png", 128, 128, NULL);
    textureDoor = new Texture("assets/deur.png", 128, 128, NULL);
    textureMap = new Texture("assets/textureMap.png", 128, 128, NULL);
    textureCameraOff = new Texture("assets/textureCameraOff.jpg", 128, 128, NULL);
    gameManager = std::make_shared<GameManager>();
    gameManager->init();
    initRoom();
    initSecurity();

    gameManager->lighting = light;
    

    // enemy1
    enemy1 = std::make_shared<GameObject>(gameManager);
    enemy1->addComponent(std::make_shared<ModelComponent>(ENEMY_PATH1));
    std::vector<EnemyComponent::EnemyLocations> enemyPath = { EnemyComponent::F, EnemyComponent::K, EnemyComponent::D, EnemyComponent::C, EnemyComponent::HALL_LEFT, EnemyComponent::A};
    std::vector<glm::vec3> positions = 
    { 
        glm::vec3(47.248f, -0.013f, -15.329f),
        glm::vec3(30.787f, -0.013f, -16.759f),
        glm::vec3(18.546f, -0.013f, -32.304f),
        glm::vec3(-8.678f, 6.574f, -16.220f),
        glm::vec3(-3.748f, -0.013f, -11.838f)        
    };
    std::vector<glm::vec3> rotations =
    {
        glm::vec3(-0.040f, 2.964f, 0),
        glm::vec3(0.003f, 3.774f, 0),
        glm::vec3(0, 4.895f, 0),
        glm::vec3(-0.220f, -0.831f, -0.088),
        glm::vec3(0, -0.083f, 0)
    };
    enemy1->position = glm::vec3(0, -1.0f, 0);
    enemy1->scale = glm::vec3(1.1f, 1.1f, 1.1f);
    enemy1->addComponent(std::make_shared<EnemyComponent>(enemyPath, positions, rotations));
    enemy1->getComponent<EnemyComponent>()->jumpscarePosition = glm::vec3(-2.770f, -0.793f, -4.846f);
    enemy1->getComponent<EnemyComponent>()->jumpscareRotation = glm::vec3(0.264f, -1.726f, 0);
    enemy1->getComponent<EnemyComponent>()->init();
    enemy1->getComponent<EnemyComponent>()->isFrozen = true;
    gameManager->enemy1 = enemy1;
    gameObjects.push_back(enemy1);

    // enemy2
    enemy2 = std::make_shared<GameObject>(gameManager);
    enemy2->addComponent(std::make_shared<ModelComponent>(ENEMY_PATH2));
    std::vector<EnemyComponent::EnemyLocations> enemyPath2 = { EnemyComponent::G, EnemyComponent::K, EnemyComponent::J, EnemyComponent::K, EnemyComponent::HALL_RIGHT, EnemyComponent::A };
    std::vector<glm::vec3> positions2 =
    {
        glm::vec3(49.010f, -0.044f, -3.964f),
        glm::vec3(27.615f, -0.044f, -2.662f),
        glm::vec3(-9.139, 6.387f, 6.609f),
        glm::vec3(20.615f, -0.044f, -2.662f),
        glm::vec3(-2.341f, -0.044f, 2.624f)
        
    };
    std::vector<glm::vec3> rotations2 =
    {
        glm::vec3(-0.040f, 2.964f, 0),
        glm::vec3(0, 5.624f, 0),
        glm::vec3(0.573f, 3.757f, 0.352f),
        glm::vec3(0, 5.624f, 0),
        glm::vec3(0.003f, 3.774f, 0)
        
    };

    enemy2->position = glm::vec3(0, -1.0f, 0);
    enemy2->scale = glm::vec3(1.1f, 1.1f, 1.1f);
    enemy2->addComponent(std::make_shared<EnemyComponent>(enemyPath2, positions2, rotations2));
    enemy2->getComponent<EnemyComponent>()->jumpscarePosition = glm::vec3(-2.341f, -1.013f, -4.424f);
    enemy2->getComponent<EnemyComponent>()->jumpscareRotation = glm::vec3(0, 4.920f, 0);
    enemy2->getComponent<EnemyComponent>()->attackFromLeft = false;
    enemy2->getComponent<EnemyComponent>()->init();
    enemy2->getComponent<EnemyComponent>()->isFrozen = false;
    gameManager->enemy2 = enemy2;
    gameObjects.push_back(enemy2);

    // enemy3
    enemy3 = std::make_shared<GameObject>(gameManager);
    enemy3->addComponent(std::make_shared<ModelComponent>(ENEMY_PATH3));
    std::vector<EnemyComponent::EnemyLocations> enemyPath3 = { EnemyComponent::B, EnemyComponent::I, EnemyComponent::K, EnemyComponent::E, EnemyComponent::HALL_LEFT, EnemyComponent::A };
    std::vector<glm::vec3> positions3 =
    {
        glm::vec3(-1.322f, 6.154f, 0.529f),
        glm::vec3(11.404, -0.013f, 23.770f),
        glm::vec3(14.048f, -0.013f, -4.425f),
        glm::vec3(37.445f, -0.013f, -36.563f),
        glm::vec3(-3.748f, -0.013f, -11.838f)
    };
    std::vector<glm::vec3> rotations3 =
    {
        glm::vec3(-1.362f, 5.683f, -0.969),
        glm::vec3(0, 5.712f, 0),
        glm::vec3(0, 6.064f, 0),
        glm::vec3(0, 5.623f, 0),
        glm::vec3(0, -0.083f, 0)
    };
    enemy3->position = glm::vec3(0, -1.0f, 0);
    enemy3->scale = glm::vec3(2.1f, 2.1f, 2.1f);
    enemy3->addComponent(std::make_shared<EnemyComponent>(enemyPath3, positions3, rotations3));
    enemy3->getComponent<EnemyComponent>()->jumpscarePosition = glm::vec3(-3.651f, -2.203f, -4.365f);
    enemy3->getComponent<EnemyComponent>()->jumpscareRotation = glm::vec3(-0.705f, -1.022f, 5.683f);
    enemy3->getComponent<EnemyComponent>()->init();
    enemy3->getComponent<EnemyComponent>()->isFrozen = false;
    gameManager->enemy3 = enemy3;
    gameObjects.push_back(enemy3);

    runningEnemy = std::make_shared<GameObject>(gameManager);
    runningEnemy->addComponent(std::make_shared<ModelComponent>(ENEMY_PATH3));
    runningEnemy->addComponent(std::make_shared<RunningEnemyComponent>());
    runningEnemy->getComponent<RunningEnemyComponent>()->init();
    runningEnemy->getComponent<RunningEnemyComponent>()->isFrozen = true;
    runningEnemy->scale = glm::vec3(2.1f, 2.1f, 2.1f);
    gameManager->runningEnemy = runningEnemy;
    gameObjects.push_back(runningEnemy);

    // Create and add DebugComponent
    debugPlayer = std::make_shared<GameObject>(gameManager);
    auto debugComponent2 = std::make_shared<DebugComponent>();
    
    debugPlayer->addComponent(debugComponent2);
    //debugPlayer->addComponent(std::make_shared<DoubleTextComponent>(15, 400, 400, 100));
    debugPlayer->position = glm::vec3(0, 2, 0);
    gameManager->player = debugPlayer;
    gameObjects.push_back(debugPlayer);

    // Create and add object3
    object3 = std::make_shared<GameObject>(gameManager);
    object3->position = glm::vec3(-5.027f, 2, -4.187f);
    object3->rotation = glm::vec3(0, 1.6f, 0);
    object3->addComponent(std::make_shared<CameraComponent>(1.0f, 1.0f));
    object3->addComponent(std::make_shared<VisionComponent>());
    object3->addComponent(std::make_shared<DoubleTextComponent>(10, 580, 350, 50, 650, 50));
    object3->getComponent<VisionComponent>()->init();
    gameManager->player = object3;
    gameObjects.push_back(object3);

    texture->bind();
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

void buildFbo()
{
    // Find the SecurityCameraComponent for the selectedCamera
    std::shared_ptr<SecurityCameraComponent> selectedCameraComponent;
    for (auto& go : gameObjects)
    {
        auto cameraComponent = go->getComponent<SecurityCameraComponent>();
        if (cameraComponent && cameraComponent->id == selectedCamera)
        {
            selectedCameraComponent = cameraComponent;
            break;
        }
    }

    if (!selectedCameraComponent)
    {
        std::cerr << "Selected camera not found!" << std::endl;
        return;
    }

    fbo->bind();
    glViewport(selectedCameraComponent->viewportX, selectedCameraComponent->viewportY, selectedCameraComponent->viewportWidth, selectedCameraComponent->viewportHeight);
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);

    tigl::shader->setProjectionMatrix(projection);

    // Set view matrix based on the camera's position and rotation
    glm::mat4 viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::rotate(viewMatrix, selectedCameraComponent->rotation.x, glm::vec3(1, 0, 0));
    viewMatrix = glm::rotate(viewMatrix, selectedCameraComponent->rotation.y, glm::vec3(0, 1, 0));
    viewMatrix = glm::rotate(viewMatrix, selectedCameraComponent->rotation.z, glm::vec3(0, 0, 1));
    viewMatrix = glm::translate(viewMatrix, -selectedCameraComponent->position);

    tigl::shader->setViewMatrix(viewMatrix);

    tigl::shader->setModelMatrix(glm::mat4(1.0f));
    tigl::shader->enableTexture(true);

    for (auto& go : gameObjects)
        go->draw();

    fbo->unbind();
}

void draw()
{
    glClearColor(0.3f, 0.4f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, 1920, 1080);
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glm::mat4 projection = glm::perspective(glm::radians(75.0f), viewport[2] / (float)viewport[3], 0.01f, 1000.0f);
    tigl::shader->enableLighting(true);

    tigl::shader->setProjectionMatrix(projection);

    if (pauseCamera)
        tigl::shader->setViewMatrix(currentMatrix);
    else
    {
        tigl::shader->setViewMatrix(object3->getComponent<CameraComponent>()->getMatrix());
        //tigl::shader->setViewMatrix(getDebugMatrix());
    }

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
    light = std::make_shared<GameObject>();
    light->position = glm::vec3(-4.032f, 6, -4.5f);
    auto lightComponent = std::make_shared<LightComponent>();
    lightComponent->diffuse = glm::vec3(0.437f, 0.547f, 0.516f);
    lightComponent->ambient = glm::vec3(1.0f, 1.0f, 1.0f);
    light->addComponent(lightComponent);
    gameObjects.push_back(light);

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
    securityDoor->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 0, false, 5, 7, textureDoor, 0));
    securityDoor->addComponent(std::make_shared<SecurityDoorComponent>());
    gameManager->rightDoor = securityDoor;
    gameObjects.push_back(securityDoor);

    securityDoor1 = std::make_shared<GameObject>(gameManager);
    securityDoor1->position = glm::vec3(-6.640f, 0, -9.486f);
    securityDoor1->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 0, false, 5, 7, textureDoor, 0, true));
    securityDoor1->addComponent(std::make_shared<SecurityDoorComponent>());
    gameManager->leftDoor = securityDoor1;
    gameObjects.push_back(securityDoor1);

    auto mapObject = std::make_shared<GameObject>();
    mapObject->position = glm::vec3(-2.0f, 0, -0.5f);
    mapObject->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 1, false, 2, 2, textureMap, 0));
    gameObjects.push_back(mapObject);

    auto gameOverCage = std::make_shared<GameObject>();
    gameOverCage->position = glm::vec3(-25, 0, -10);
    gameOverCage->scale = glm::vec3(0.5f, 0.5f, 0.5f);
    gameOverCage->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 0, false, 7, 7, new Texture("assets/game_over.png", NULL, NULL, NULL), 0));
    gameObjects.push_back(gameOverCage);

    auto gameOverBlackScreen = std::make_shared<GameObject>();
    gameOverBlackScreen->position = glm::vec3(-32, -4, -10.2);
    gameOverBlackScreen->scale = glm::vec3(2.5f, 2.5f, 2.5f);
    gameOverBlackScreen->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 0, false, 7, 7, new Texture("assets/game_over.png", NULL, NULL, NULL), 0));
    gameObjects.push_back(gameOverBlackScreen);

    cameraSystemToggler = std::make_shared<GameObject>(gameManager);
    cameraSystemToggler->position = glm::vec3(-1.01f, 0, -2.5f);
    cameraSystemToggler->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 1, false, 4, 3, textureCameraOff, 0, true));
    cameraSystemToggler->addComponent(std::make_shared<CameraSystemToggleComponent>());
    gameManager->cameraSystemToggler = cameraSystemToggler;
    gameObjects.push_back(cameraSystemToggler);

    auto winScreen = std::make_shared<GameObject>();
    winScreen->position = glm::vec3(-25, 0, -60);
    winScreen->scale = glm::vec3(0.5f, 0.5f, 0.5f);
    winScreen->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 0, false, 7, 7, new Texture("assets/win_screen.png", NULL, NULL, NULL), 0));
    gameObjects.push_back(winScreen);

    auto winsScreenBig = std::make_shared<GameObject>();
	winsScreenBig->position = glm::vec3(-32, -4, -60.2);
    winsScreenBig->scale = glm::vec3(6.5f, 6.5f, 6.5f);
    winsScreenBig->addComponent(std::make_shared<RectangleComponent>(0, 0, 0, 0, false, 7, 7, new Texture("assets/win_screen.png", NULL, NULL, NULL), 0));
    gameObjects.push_back(winsScreenBig);
    
    auto tafel = std::make_shared<GameObject>();
    tafel->position = glm::vec3(48.0f, 0, -1.0f);
    tafel->addComponent(std::make_shared<ModelComponent>("assets/models/pikniekTafel/picnicTafel.obj"));
    tafel->scale = glm::vec3(1.5, 1.5, 1.5);
    gameObjects.push_back(tafel);

    auto tafel2 = std::make_shared<GameObject>();
    tafel2->position = glm::vec3(48.0f, 0, 2.0f);
    tafel2->addComponent(std::make_shared<ModelComponent>("assets/models/pikniekTafel/picnicTafel.obj"));
    tafel2->scale = glm::vec3(1.5, 1.5, 1.5);
    gameObjects.push_back(tafel2);

    auto tafel3 = std::make_shared<GameObject>();
    tafel3->position = glm::vec3(48.0f, 0, 5.0f);
    tafel3->addComponent(std::make_shared<ModelComponent>("assets/models/pikniekTafel/picnicTafel.obj"));
    tafel3->scale = glm::vec3(1.5, 1.5, 1.5);
    gameObjects.push_back(tafel3);

    auto tafel4 = std::make_shared<GameObject>();
    tafel4->position = glm::vec3(42.0f, 0, -1.0f);
    tafel4->addComponent(std::make_shared<ModelComponent>("assets/models/pikniekTafel/picnicTafel.obj"));
    tafel4->scale = glm::vec3(1.5, 1.5, 1.5);
    gameObjects.push_back(tafel4);

    auto tafel5 = std::make_shared<GameObject>();
    tafel5->position = glm::vec3(42.0f, 0, 2.0f);
    tafel5->addComponent(std::make_shared<ModelComponent>("assets/models/pikniekTafel/picnicTafel.obj"));
    tafel5->scale = glm::vec3(1.5, 1.5, 1.5);
    gameObjects.push_back(tafel5);

    auto tafel6 = std::make_shared<GameObject>();
    tafel6->position = glm::vec3(42.0f, 0, 5.0f);
    tafel6->addComponent(std::make_shared<ModelComponent>("assets/models/pikniekTafel/picnicTafel.obj"));
    tafel6->scale = glm::vec3(1.5, 1.5, 1.5);
    gameObjects.push_back(tafel6);

    auto roeloeTafel = std::make_shared<GameObject>();
    roeloeTafel->position = glm::vec3(46.0f, 1, -19.0f);
    roeloeTafel->addComponent(std::make_shared<ModelComponent>("assets/models/roeloeTafel/roeloeTafel2.obj"));
    roeloeTafel->scale = glm::vec3(0.15, 0.15, 0.15);
    gameObjects.push_back(roeloeTafel);

    auto toy = std::make_shared<GameObject>();
    toy->position = glm::vec3(30.0f, 2, -34.0f);
    toy->addComponent(std::make_shared<ModelComponent>("assets/models/toy/toy.obj"));
    toy->scale = glm::vec3(3, 3, 3);
    toy->rotation = glm::vec3(0, -90, 0);
    gameObjects.push_back(toy);

    auto arcade = std::make_shared<GameObject>();
    arcade->position = glm::vec3(21.0f, 0, -38.0f);
    arcade->addComponent(std::make_shared<ModelComponent>("assets/models/arcade/arcade.obj"));
    arcade->scale = glm::vec3(0.02, 0.02, 0.02);
    arcade->rotation = glm::vec3(0, 0, 0);
    gameObjects.push_back(arcade);

    auto arcade2 = std::make_shared<GameObject>();
    arcade2->position = glm::vec3(18.0f, 0, -38.0f);
    arcade2->addComponent(std::make_shared<ModelComponent>("assets/models/arcade/arcade.obj"));
    arcade2->scale = glm::vec3(0.02, 0.02, 0.02);
    arcade2->rotation = glm::vec3(0, 0, 0);
    gameObjects.push_back(arcade2);

    auto arcade3 = std::make_shared<GameObject>();
    arcade3->position = glm::vec3(15.0f, 0, -38.0f);
    arcade3->addComponent(std::make_shared<ModelComponent>("assets/models/arcade/arcade.obj"));
    arcade3->scale = glm::vec3(0.02, 0.02, 0.02);
    arcade3->rotation = glm::vec3(0, 0, 0);
    gameObjects.push_back(arcade3);

}

void initSecurity() 
{
    auto screenObject = std::make_shared<GameObject>();
    screenObject->position = glm::vec3(-6, 0, 7.5);
    auto screenComponent = std::make_shared<ScreenComponent>(5, 0, -10, 1, false, 4, 3, fbo.get());
    screenObject->addComponent(screenComponent);
    gameObjects.push_back(screenObject);

    auto RoomObjCameraB = std::make_shared<GameObject>();
    auto RoomCompCameraB = std::make_shared<SecurityCameraComponent>(1, 0, 0, 800, 600, glm::vec3(0.468, 9.8, -0.748), glm::vec3(0.748, 0.935, 0));
    RoomObjCameraB->addComponent(RoomCompCameraB);
    gameObjects.push_back(RoomObjCameraB);

    auto RoomObjCameraC = std::make_shared<GameObject>();
    auto RoomCompCameraC = std::make_shared<SecurityCameraComponent>(2, 0, 0, 800, 600, glm::vec3(-9.346, 9.8, -15.888), glm::vec3(0.650, 0.747, 0));
    RoomObjCameraC->addComponent(RoomCompCameraC);
    gameObjects.push_back(RoomObjCameraC);

    auto RoomObjCameraD = std::make_shared<GameObject>();
    auto RoomCompCameraD = std::make_shared<SecurityCameraComponent>(3, 0, 0, 800, 600, glm::vec3(10.352, 9.8, -25.727), glm::vec3(0.622, 0.846, 0));
    RoomObjCameraD->addComponent(RoomCompCameraD);
    gameObjects.push_back(RoomObjCameraD);

    auto RoomObjCameraE = std::make_shared<GameObject>();
    auto RoomCompCameraE = std::make_shared<SecurityCameraComponent>(4, 0, 0, 800, 600, glm::vec3(25.154, 9.8, -25.464), glm::vec3(0.622, 0.819, 0));
    RoomObjCameraE->addComponent(RoomCompCameraE);
    gameObjects.push_back(RoomObjCameraE);

    auto RoomObjCameraF = std::make_shared<GameObject>();
    auto RoomCompCameraF = std::make_shared<SecurityCameraComponent>(5, 0, 0, 800, 600, glm::vec3(38.729, 9.8, -23.083), glm::vec3(0.687, 2.352, 0));
    RoomObjCameraF->addComponent(RoomCompCameraF);
    gameObjects.push_back(RoomObjCameraF);

    auto RoomObjCameraG = std::make_shared<GameObject>();
    auto RoomCompCameraG = std::make_shared<SecurityCameraComponent>(6, 0, 0, 800, 600, glm::vec3(38.729, 9.8, 9.164), glm::vec3(0.687, 0.767, 0));
    RoomObjCameraG->addComponent(RoomCompCameraG);
    gameObjects.push_back(RoomObjCameraG);

    auto RoomObjCameraH = std::make_shared<GameObject>();
    auto RoomCompCameraH = std::make_shared<SecurityCameraComponent>(7, 0, 0, 800, 600, glm::vec3(25.154, 9.8, 11.543), glm::vec3(0.661, 2.3, 0));
    RoomObjCameraH->addComponent(RoomCompCameraH);
    gameObjects.push_back(RoomObjCameraH);

    auto RoomObjCameraI = std::make_shared<GameObject>();
    auto RoomCompCameraI = std::make_shared<SecurityCameraComponent>(8, 0, 0, 800, 600, glm::vec3(10.662, 9.8, 11.543), glm::vec3(0.661, 2.3, 0));
    RoomObjCameraI->addComponent(RoomCompCameraI);
    gameObjects.push_back(RoomObjCameraI);

    auto RoomObjCameraJ = std::make_shared<GameObject>();
    auto RoomCompCameraJ = std::make_shared<SecurityCameraComponent>(9, 0, 0, 800, 600, glm::vec3(-8.766, 9.8, 6.521), glm::vec3(0.661, 2.3, 0));
    RoomObjCameraJ->addComponent(RoomCompCameraJ);
    gameObjects.push_back(RoomObjCameraJ);

    auto RoomObjCameraK = std::make_shared<GameObject>();
    auto RoomCompCameraK = std::make_shared<SecurityCameraComponent>(10, 0, 0, 800, 600, glm::vec3(10.661, 9.8, 9.691), glm::vec3(0.556, 0.767, 0));
    RoomObjCameraK->addComponent(RoomCompCameraK);
    gameObjects.push_back(RoomObjCameraK);
}

