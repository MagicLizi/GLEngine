#include <iostream>
#include "GLManager.h"
#include "GLObject.h"
#include "ShaderManager.h"
#include <glm/glm.hpp>
#include <list>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;

void engineTestRender(GLManager *glManager);

int main()
{

    cout << "Begin GLEngine" << endl;

    GLManager *glManager = new GLManager(1280, 800);

    bool initSuccess = glManager->init();
    // glManager->setLineMode(true);
    if (initSuccess)
    {
        cout << "Init GLEngine Success!" << endl;
        engineTestRender(glManager);
    }

    glManager->terminate();

    return 0;
}

void engineTestRender(GLManager *glManager)
{
    float vertices[] = {
        -0.5, -0.5, -0.5, 1.0f, 0.5f, 0.31f, 0, 0,
        0.5, -0.5, -0.5, 1.0f, 0.5f, 0.31f, 1, 0,
        0.5, 0.5, -0.5, 1.0f, 0.5f, 0.31f, 1, 1,
        -0.5, 0.5, -0.5, 1.0f, 0.5f, 0.31f, 0, 1,

        -0.5, -0.5, 0.5, 1.0f, 0.5f, 0.31f, 0, 0,
        0.5, -0.5, 0.5, 1.0f, 0.5f, 0.31f, 1, 0,
        0.5, 0.5, 0.5, 1.0f, 0.5f, 0.31f, 1, 1,
        -0.5, 0.5, 0.5, 1.0f, 0.5f, 0.31f, 0, 1};

    int indexVec[] = {
        0, 1, 2, // 第一个三角形
        2, 3, 0,
        4, 5, 6,
        6, 7, 4,
        3, 2, 6,
        6, 7, 3,
        0, 1, 5,
        5, 4, 0,
        1, 5, 6,
        6, 2, 1,
        0, 4, 7,
        7, 3, 0};

    GLObject *obj1 = new GLObject(vertices, sizeof(vertices), indexVec, sizeof(indexVec), "test", {"src/resources/container.jpg", "src/resources/awesomeface.png"});
    obj1->rotate = glm::vec3(0, 0, 45);
    obj1->scale = glm::vec3(0.5, 0.5, 0.5);
    obj1->color = glm::vec3(1.0f, 0.5f, 0.31f);

    GLObject *obj2 = new GLObject(vertices, sizeof(vertices), indexVec, sizeof(indexVec), "light1", {});
    obj2->pos = glm::vec3(1, 0, 0);
    obj2->rotate = glm::vec3(0, 0, 45);
    obj2->scale = glm::vec3(0.25, 0.25, 0.25);

    list<GLObject> objects;
    objects.push_back(*obj1);
    objects.push_back(*obj2);

    glManager->renderLoop(objects);
}