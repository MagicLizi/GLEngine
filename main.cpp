#include <iostream>
#include "GLManager.h"
#include "GLObject.h"
#include "ShaderManager.h"
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
        0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f   // top left
    };

    int indexVec[] = {
        0, 1, 3, // 第一个三角形
        1, 2, 3  // 第二个三角形
    };

    GLObject *obj1 = new GLObject(vertices, sizeof(vertices), indexVec, sizeof(indexVec), "test", {"src/resources/container.jpg", "src/resources/awesomeface.png"});
    glManager->renderLoop(obj1, true);
}