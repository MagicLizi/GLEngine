#include "GLManager.h"
#include <iostream>
#include "ShaderManager.h"
#include "GLObject.h"
using namespace std;
void framebuffer_size_callback(GLFWwindow *window, int width, int height);

GLManager::GLManager(int mWidth, int mHeight)
{
    width = mWidth;
    height = mHeight;
}

GLManager::~GLManager()
{
    terminate();
}

bool GLManager::init()
{
    bool result = initGLFW() & initGLAD();
    cout << "GLManager::init Result:" << result << endl;
    return result;
}

bool GLManager::initGLFW()
{
    cout << "-----begin initGLFW-----" << endl;
    glfwInit();
    //设置opengl版本以及相关的渲染模式 设置window的hint
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //macOS开启向前兼容
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glWindow = glfwCreateWindow(width, height, "GLManager", NULL, NULL);
    if (glWindow == NULL)
    {
        return false;
    }
    glfwMakeContextCurrent(glWindow);
    setGLViewPortAndCallbacks();
    return true;
}

bool GLManager::initGLAD()
{
    cout << "-----begin initGLAD-----" << endl;
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return false;
    }
    return true;
}

void GLManager::terminate()
{
    glfwTerminate();
}

void GLManager::version()
{
    // 在初始化及创建窗口后
    std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    //当前顶点属性的数量
    int nVertexAtrributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nVertexAtrributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nVertexAtrributes << std::endl;
}

void GLManager::renderLoop(GLObject *drawObj)
{

    while (!glfwWindowShouldClose(glWindow))
    {
        //处理输入
        processInput();

        //清除背景
        glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.alpha);
        glClear(GL_COLOR_BUFFER_BIT);

        //draw
        drawObj->draw();

        //交换缓冲区
        glfwSwapBuffers(glWindow);
        //事件
        glfwPollEvents();
    }
}

void GLManager::setBackgroundColor(EngineColor color)
{
    backgroundColor = color;
}

void GLManager::setLineMode(bool line)
{
    if (line)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void GLManager::setGLViewPortAndCallbacks()
{
    glfwSetFramebufferSizeCallback(glWindow, framebuffer_size_callback);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void GLManager::processInput()
{
    if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(glWindow, true);
    }
}