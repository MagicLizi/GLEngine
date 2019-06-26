#include <iostream>
#include "GLManager.h"
#include "ShaderManager.h"
using namespace std;

int main()
{
    cout << "Begin GLEngine" << endl;
    GLManager glManager(1280, 700);

    bool initSuccess = glManager.init();

    if (initSuccess)
    {
        glManager.version();
        cout << "Init GLEngine Success!" << endl;
        EngineColor bColor = {1, 1, 1, 0.5};
        glManager.setBackgroundColor(bColor);
        glManager.renderLoop();
    }

    glManager.terminate();
    return 0;
}
