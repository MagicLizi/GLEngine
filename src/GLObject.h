#ifndef GLOBJECT_H
#define GLOBJECT_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ShaderManager.h"
#include <string>
#include <list>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
class GLObject
{
public:
    GLObject(float m_vertices[], GLuint verSize, string shaderName);
    GLObject(float m_vertices[], GLuint verSize, int m_indices[], GLuint indiceSize, string shaderName, list<string> paths);
    ~GLObject();
    void render();
    void draw();
    void drawvao(GLuint m_vao);
    void drawIndex();
    GLuint vao;
    glm::vec3 pos = glm::vec3(0, 0, 0);
    glm::vec3 scale = glm::vec3(1, 1, 1);
    glm::vec3 rotate = glm::vec3(0, 0, 0);
    glm::vec3 color = glm::vec3(1, 1, 1);
    glm::mat4 updateTransform();
    void updateObjColor();
    bool isIndex = true;

private:
    ShaderManager *shader;
    GLuint createTexture(const char *texturePath);
    list<GLuint> textures;
    int drawSize;
};
#endif