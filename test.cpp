#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
    string path = "src/shaders/test.vert";
    cout << "loadShaderCode from:" << path << endl;
    string shaderCode;
    ifstream fileStream;
    fileStream.exceptions(ifstream::badbit);
    try
    {
        fileStream.open(path);
        ostringstream codeStream;
        codeStream << fileStream.rdbuf();
        fileStream.close();

        shaderCode = codeStream.str();
        cout << "load Code success \n"
             << shaderCode << endl;
    }
    catch (ifstream::failure e)
    {
        cout << "load Code error " << endl;
    }
    return 0;
}
