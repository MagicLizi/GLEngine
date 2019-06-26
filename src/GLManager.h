#ifndef GLMANAGER_H
#define GLMANAGER_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"

struct EngineColor
{
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat alpha;
};

class GLManager
{
public:
    GLManager(int mWidth, int mHeight);
    ~GLManager();
    bool init();
    void terminate();
    void version();
    void renderLoop();
    void setLineMode(bool line);
    void setBackgroundColor(EngineColor color);

private:
    int width;
    int height;
    GLFWwindow *glWindow;
    EngineColor backgroundColor = {0, 0, 0, 0};
    bool initGLFW();
    bool initGLAD();
    void setGLViewPortAndCallbacks();
    void processInput();
};

#endif