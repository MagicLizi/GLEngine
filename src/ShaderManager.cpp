#include "ShaderManager.h"
ShaderManager::ShaderManager(string name, ConfigUniform m_cufun = NULL)
{
    cufun = m_cufun;
    string vPath = basicPath + name + ".vert";
    string fPath = basicPath + name + ".frag";
    GLuint vertexShader = loadShader(vPath, GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader(fPath, GL_FRAGMENT_SHADER);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 1024, NULL, infoLog);
        cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << infoLog << endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint ShaderManager::loadShader(string filePath, GLenum shaderType)
{
    cout << "loadShaderCode from:" << filePath << endl;
    string str;
    ifstream fileStream;
    fileStream.exceptions(ifstream::badbit);
    try
    {
        fileStream.open(filePath);
        ostringstream codeStream;
        codeStream << fileStream.rdbuf();
        codeStream << '\0';
        fileStream.close();

        str = codeStream.str();
        cout << "load Code success length:" << str.length() << endl;
        cout << str << endl;
    }
    catch (ifstream::failure e)
    {
        cout << "load Code error " << endl;
    }
    const char *shaderCode = str.c_str();
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderCode, NULL);
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

void ShaderManager::useShader()
{
    glUseProgram(shaderProgram);
    if (cufun != NULL)
    {
        cufun(shaderProgram);
    }
}

void ShaderManager::setInt(string name, int value)
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
}

void ShaderManager::setMatrix(string name, const GLfloat *matrix)
{
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name.c_str()), 1, GL_FALSE, matrix);
}

void ShaderManager::setVec3(string name, float x, float y, float z)
{
    glUniform3f(glGetUniformLocation(shaderProgram, name.c_str()), x, y, z);
}