#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H
#define GL_SILENCE_DEPRECATION
#include <string>
#include "GLFW/glfw3.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
typedef void (*ConfigUniform)(GLuint shaderProgram);
class ShaderManager
{
public:
    string basicPath = "src/shaders/";
    ShaderManager(string name, ConfigUniform m_cufun);
    GLuint shaderProgram;
    void useShader();
    ConfigUniform cufun;
    void setInt(string name, int value);

private:
    void initShaderProgram();
    GLuint loadShader(string filePath, GLenum shaderType);
};
#endif