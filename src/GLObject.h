#ifndef GLOBJECT_H
#define GLOBJECT_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ShaderManager.h"
#include <string>
using namespace std;
class GLObject
{
public:
    GLObject(float m_vertices[], GLuint verSize, string shaderName);
    GLObject(float m_vertices[], GLuint verSize, int m_indices[], GLuint indiceSize, string shaderName, const char *texturePath);
    ~GLObject();
    void draw();
    void drawvao(GLuint m_vao);
    void drawIndex();
    GLuint vao;

private:
    ShaderManager *shader;
    void createTexture(const char *texturePath);
};
#endif