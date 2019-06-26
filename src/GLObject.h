#ifndef GLOBJECT_H
#define GLOBJECT_H
#include <string>
#include "ShaderManager.h"
using namespace std;
class GLObject
{
public:
    GLObject(float vertices[], string shaderName);
    ~GLObject();

private:
    ShaderManager shader;
};
#endif