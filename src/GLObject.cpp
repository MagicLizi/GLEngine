#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "GLObject.h"
#include <math.h>

void test(GLuint shaderProgram)
{
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "uColor");
    glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
}

glm::mat4 transformTest()
{
    glm::mat4 idMat = glm::mat4(1.0);
    idMat = glm::rotate(idMat, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    // idMat = glm::translate(idMat, glm::vec3(0.25, 0, 0));
    idMat = glm::scale(idMat, glm::vec3(0.5, 0.5, 0.5));
    return idMat;
}

glm::mat4 modelMatTest()
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    return model;
}

glm::mat4 viewMatTest()
{
    glm::mat4 view = glm::mat4(1.0);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    return view;
}

void lightTest(ShaderManager *shader)
{
    shader->setVec3("objColor", 1.0f, 0.5f, 0.31f);
    shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
}

glm::mat4 projMatTest()
{
    glm::mat4 projection = glm::mat4(1.0);
    projection = glm::perspective(glm::radians(45.0f), (float)1280 / (float)800, 0.1f, 100.0f);
    return projection;
}

glm::mat4 GLObject::updateTransform()
{
    glm::mat4 transMat = glm::mat4(1.0);
    transMat = glm::rotate(transMat, glm::radians(rotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transMat = glm::rotate(transMat, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    transMat = glm::rotate(transMat, glm::radians(rotate.z), glm::vec3(0.0f, 0.0f, 1.0f));
    transMat = glm::translate(transMat, pos);
    transMat = glm::scale(transMat, scale);
    return transMat;
}

void GLObject::updateObjColor()
{
    shader->setVec3("objColor", color.x, color.y, color.z);
}

GLObject::GLObject(float m_vertices[], GLuint verSize, int m_indices[], GLuint indiceSize, string shaderName, list<string> tpaths)
{
    drawSize = indiceSize;
    //加载shader
    ConfigUniform cunf = NULL; //设置uniform
    shader = new ShaderManager(shaderName, cunf);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo, ebo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verSize, m_vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiceSize, m_indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
    // glEnableVertexAttribArray(2);

    //加载纹理
    shader->useShader();
    shader->setMatrix("model", glm::value_ptr(updateTransform()));
    shader->setMatrix("view", glm::value_ptr(viewMatTest()));
    shader->setMatrix("proj", glm::value_ptr(projMatTest()));

    //设置光照
    shader->setVec3("lightColor", 1.0f, 1.0f, 1.0f);
    shader->setVec3("lightPos", 1.2f, 1.0f, 2.0f);
    shader->setVec3("viewPos", 0, 0, 10);
    shader->setVec3("material.ambient", 1.0f, 1.0f, 1.0f);
    shader->setVec3("material.diffuse", 1.0f, 1.0f, 1.0f);
    shader->setVec3("material.specular", 0.5, 0.5, 0.5);
    shader->setFloat("material.shininess", 32.0f);

    updateObjColor();
    list<string>::iterator it;
    int i = 0;
    for (it = tpaths.begin(); it != tpaths.end(); it++)
    {
        const char *p = it->c_str();
        GLuint texture = createTexture(p);
        string textureName = "texture";
        textureName = textureName.append(to_string(i));
        shader->setInt(textureName, i);
        textures.push_back(texture);
        i++;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

GLObject::GLObject(float m_vertices[], GLuint verSize, string shaderName)
{
    ConfigUniform cunf = NULL; //设置uniform
    shader = new ShaderManager(shaderName, cunf);

    glGenVertexArrays(1, &vao); //获取vao index
    glBindVertexArray(vao);     //绑定 启用 index

    GLuint vbo; //数据对象
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verSize, m_vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLObject::~GLObject()
{
}

GLuint GLObject::createTexture(const char *texturePath)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    //设置 s（x） 和 t （y） 上的warp 方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    //设置放大和缩小的过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
    stbi_set_flip_vertically_on_load(true);
    if (data)
    {
        if (nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        cout << "cannot load texture:" << texturePath << endl;
    }
    stbi_image_free(data);
    return texture;
}

void GLObject::render()
{
    if (isIndex)
    {
        drawIndex();
    }
    else
    {
        draw();
    }
}

void GLObject::drawIndex()
{
    //texture
    list<GLuint>::iterator it;
    int i = 0;
    for (it = textures.begin(); it != textures.end(); it++)
    {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, *it);
        i++;
    }
    shader->useShader();
    shader->setMatrix("model", glm::value_ptr(updateTransform()));
    updateObjColor();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, drawSize, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void GLObject::draw()
{
    shader->useShader();
    shader->setMatrix("model", glm::value_ptr(updateTransform()));
    updateObjColor();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, drawSize);
    glBindVertexArray(0);
}

void GLObject::drawvao(GLuint m_vao)
{
    shader->useShader();
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}