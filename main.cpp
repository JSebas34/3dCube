#ifdef _WIN32
    #include "src\glad_Windows_NT\glad.h"
#elif __APPLE__
    #include "glad_Darwin\glad.h"
#else
    #error "Unsupported platform"
#endif
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>
#include <SFML/Window.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>
#include <functions.cpp>

using namespace std;

int main()
{
    
    sf::Window window(sf::VideoMode({1600,800}), "wakawaka");
    window.setVerticalSyncEnabled(true);

    window.setActive(true); 

    GLuint VBO = 0, VAO = 0;

    string vertexCode = loadShader("Vshader.glsl");
    string fragmentCode = loadShader("Fshader.glsl");

    GLuint vertexShader = compileShaders(GL_VERTEX_SHADER, vertexCode);
    GLuint fragmentShader = compileShaders(GL_FRAGMENT_SHADER, fragmentCode);

    GLuint shaderProgram = glCreateProgram();       //program to attach shaders together
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);       //link the shaders to the prgram after being attatched

    glDeleteShader(vertexShader);       //delete shaders since they are now in the program and rendered unnecessary
    glDeleteShader(fragmentShader);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");   //pos of atributtes

    bufferProcess(VBO, VAO, posAttrib);

    glEnableVertexAttribArray(posAttrib); //enables attributes
    
    while (window.isOpen()) {

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
        }
    }
        

    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);        //use program

    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES,0,3);

    glBindVertexArray(0);


}
return 0;
}