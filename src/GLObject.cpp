#include "GLObject.h"

GLObject::GLObject(float m_vertices[], GLuint verSize, string shaderName)
{
    shader = new ShaderManager(shaderName);

    glGenVertexArrays(1, &vao); //获取vao index
    glBindVertexArray(vao);     //绑定 启用 index

    GLuint vbo; //数据对象
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verSize, m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

GLObject::~GLObject()
{
}

void GLObject::draw()
{
    shader->useShader();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

void GLObject::drawvao(GLuint m_vao)
{
    shader->useShader();
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}