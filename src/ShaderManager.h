#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H
#define GL_SILENCE_DEPRECATION
#include <string>
#include "GLFW/glfw3.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <list>
using namespace std;
class ShaderManager
{
public:
    string basicPath = "src/shaders/";
    ShaderManager(string name);
    GLuint shaderProgram;
    void useShader();

private:
    void initShaderProgram();
    const GLchar *loadShaderCode(string filePath);
    GLuint loadShader(const char *shaderSource, GLenum shaderType);
    GLuint loadShaderProgram(list<unsigned int> shaders);
};
#endif