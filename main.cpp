#include <iostream>
#include "GLManager.h"
#include "GLObject.h"
using namespace std;

void engineTestRender(GLManager *glManager);

int main()
{
    cout << "Begin GLEngine" << endl;

    GLManager *glManager = new GLManager(1280, 800);

    bool initSuccess = glManager->init();

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
    glManager->setLineMode(true);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f    // top
    };
    GLObject *obj1 = new GLObject(vertices, sizeof(vertices), "test");

    glManager->renderLoop(obj1);
}