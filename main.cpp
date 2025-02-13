#ifdef _WIN32
    #include "glad_Windows_NT/glad.h"
#elif __APPLE__
    #include "glad_Darwin/glad.h"
#else
    #error "Unsupported platform"
#endif
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

    glDeleteShader(vertexShader);       //delete shaders since they are now in the program and rendered unnecessary
    glDeleteShader(fragmentShader);

    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");   //pos of atributtes

    glEnableVertexAttribArray(posAttrib); //enables attributes

    glUseProgram(shaderProgram);        //use program
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0, sizeof(vertices));

}
return 0;
}