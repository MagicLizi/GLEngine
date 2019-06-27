#include "ShaderManager.h"
ShaderManager::ShaderManager(string name, ConfigUniform m_cufun = NULL)
{
    cufun = m_cufun;

    GLuint vertexShader = loadShader(loadShaderCode(basicPath + name + ".vert"), GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader(loadShaderCode(basicPath + name + ".frag"), GL_FRAGMENT_SHADER);

    list<GLuint> shaders;
    shaders.push_back(vertexShader);
    shaders.push_back(fragmentShader);
    shaderProgram = loadShaderProgram(shaders);
}

const GLchar *ShaderManager::loadShaderCode(string filePath)
{
    cout << "loadShaderCode from:" << filePath << endl;
    string shaderCode;
    ifstream fileStream;
    fileStream.exceptions(ifstream::badbit);
    try
    {
        fileStream.open(filePath);
        ostringstream codeStream;
        codeStream << fileStream.rdbuf();
        fileStream.close();

        shaderCode = codeStream.str();
        cout << "load Code success length:" << shaderCode.length() << endl;
        // cout << shaderCode << endl;
    }
    catch (ifstream::failure e)
    {
        cout << "load Code error " << endl;
    }
    return shaderCode.c_str();
}

GLuint ShaderManager::loadShader(const char *shaderSource, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        cout << "compile shader error" << infoLog << endl;
    }
    return shader;
}

//加载shader program
GLuint ShaderManager::loadShaderProgram(list<GLuint> shaders)
{
    GLuint shaderProgram = glCreateProgram();
    list<GLuint>::iterator it;
    for (it = shaders.begin(); it != shaders.end(); it++)
    {
        glAttachShader(shaderProgram, *it);
    }
    glLinkProgram(shaderProgram);
    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        cout << "create shader program error" << infoLog << endl;
    }

    //清理shader
    for (it = shaders.begin(); it != shaders.end(); it++)
    {
        glDeleteShader(*it);
    }
    return shaderProgram;
}

void ShaderManager::useShader()
{
    glUseProgram(shaderProgram);
    if (cufun != NULL)
    {
        cufun(shaderProgram);
    }
}
