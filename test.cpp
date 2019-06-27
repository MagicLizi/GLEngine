#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

void testSize(float mvertices[]);

int main()
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f, // left
        0.5f, -0.5f, 0.0f,  // right
        0.0f, 0.5f, 0.0f    // top
    };
    cout << sizeof(vertices) << endl;
    testSize(vertices);
    return 0;
}

void testSize(float mvertices[])
{
    cout << sizeof(mvertices) << endl;
}
