#include <glad.h>
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functions.cpp>

using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 800), "wakawaka");
    window.setVerticalSyncEnabled(true);

    window.setActive(true);

    bool running = true;

    while (running) {
        sf::Event event;

        while (window.pollEvent(event)) {
            switch (event.type) {

            case sf::Event::Closed:
                running = false;
                break;
            }
        }
    
    
    float vertices[] = {
            0.0f, 0.5f,
            0.5f, -0.5f,
            -0.5, -0.5f
    };

    GLuint vbo; //unsingned int

    glGenBuffers(1, &vbo);      //generate buffer

    glBindBuffer(GL_ARRAY_BUFFER, vbo);     //activate/bind buffer to target

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);      //put data into the buffer


    string vertexCode = loadShader("Vshader.glsl");
    string fragmentCode = loadShader("Fshader.glsl");

    const char* vertexSource = vertexCode.c_str();      //turn into expected c string

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);     //create shader object
    glShaderSource( vertexShader, 1, &vertexSource, NULL);  //species source code for the object
    glCompileShader(vertexShader);

    const char* fragmentSource = fragmentCode.c_str();      //turn into expected c string

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); //same procces as vertex shader
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();       //program to attach shaders together
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);       //link the shaders to the prgram after being attatched
    glUseProgram(shaderProgram);        //use program

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");

    glVertexAttribPointer(posAttrib,3,GL_FLOAT,GL_FALSE,);
    return 0;
}
}