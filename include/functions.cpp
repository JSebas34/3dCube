#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

string loadShader(const string& filePath) {
    ifstream shaderfile(filePath);

    if (!shaderfile.is_open()) {
        cout << "Failed to open file :(" << filePath << endl;
        return "";
    }

    stringstream filebuffer;

    filebuffer << shaderfile.rdbuf();
    shaderfile.close();

    return filebuffer.str();
}