#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "tigl.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenCv.h"

#include "GameObject.h"
#include "DrawComponent.h"
#include "RectangleComponent.h"
#include "CameraComponent.h"
using tigl::Vertex;

#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")

GLFWwindow* window;
OpenCv openCv;
std::unique_ptr<CameraComponent> camera;

void init();
void update();
void draw();
void runOpencv();

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
    camera = std::make_unique<CameraComponent>(window);

    auto object = std::make_shared<GameObject>();
    object->position = glm::vec3(0, 0, 0);
    object->addComponent(std::make_shared<RectangleComponent>(1, 1, 1));
    gameObjects.push_back(object);

    auto object2 = std::make_shared<GameObject>();
    object2->position = glm::vec3(-1, 3, 0);
    object2->addComponent(std::make_shared<RectangleComponent>(1, 1, 1));
    gameObjects.push_back(object2);
}


void update()
{
    double currentTime = glfwGetTime();
    static double lastTime = currentTime;
    float deltaTime = float(currentTime - lastTime);

    runOpencv();
    camera->update(window);

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
    tigl::shader->setViewMatrix(camera->getMatrix());
    tigl::shader->setModelMatrix(glm::mat4(1.0f));

    

    for (auto& go : gameObjects)
		go->draw();

 
}

void runOpencv()
{
	openCv.run();
}