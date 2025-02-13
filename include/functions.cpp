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

void SetupBuffers(GLuint &VBO, GLuint &VAO, GLint posAttrib) {
    float vertices[] = {
            0.0f, 0.5f,
            0.5f, -0.5f,
            -0.5, -0.5f
    };

    glGenBuffers(1, &VBO);      //generate buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);     //activate/bind buffer to target

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);      //put data into the buffer

    glEnableVertexAttribArray(posAttrib);

    glVertexAttribPointer(posAttrib,2,GL_FLOAT,GL_FALSE,0,(void*)0);    //specifies how to interpret vbd when drawing calls

    glBindBuffer(GL_ARRAY_BUFFER,0); //unbinds
    glBindVertexArray(0); //unbinds
}