#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Window.h"
#include "Mesh.h"
#include "Shader.h"
// #include "tiny_gltf.h"

using namespace std;

void processInput(GLFWwindow*);

void printShaderInfoLog(GLuint shader) {
    int maxLength;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

    // The maxLength includes the NULL character
    char* infoLog = new char[maxLength];
    glGetShaderInfoLog(shader, maxLength, &maxLength, infoLog);

    if (maxLength > 0) {
        std::cerr << "Shader info log:" << std::endl;
        std::cerr << infoLog << std::endl;
    }

    delete[] infoLog;
}

// Removed two callback functions

int main() {

    Window window{ 800,600 };

    // Replaced all the code up to Initialization ends here with above code
    // ==================================================================
    // The Real Program starts here
    float red{};

    float vertices[]{
           -1.0f, -0.5f, 0.0f,
            0.0f, -0.5f, 0.0f,
           -0.5f,  0.5f, 0.0f,
           -1.0f, -0.5f, 0.0f,
           -0.5f,  0.5f, 0.0f,
           -1.0f, 0.5f, 0.0f
    };
    // 9*float = 36  / 1*float (4)   = 9
    Mesh mesh1{ vertices, size(vertices) };  // sizeof(vertices) / sizeof(float)

    float vertices2[]{
        0.0f, -0.5f, 0.0f,
        1.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f
    };

    Mesh mesh2{ vertices2, size(vertices2) };

    Shader vertexShader{ "VertexShader.glsl", GL_VERTEX_SHADER };

    Shader orangeShader{ "FragmentShader.glsl", GL_FRAGMENT_SHADER};

    Shader yellowShader{
        "FragmentShader.glsl", GL_FRAGMENT_SHADER };

    // -------- Create Orange Shader Program (Render Pipeline) ---------
    unsigned int orangeShaderProgram;
    orangeShaderProgram = glCreateProgram();
    glAttachShader(orangeShaderProgram, vertexShader.shaderId);
    glAttachShader(orangeShaderProgram, orangeShader.shaderId);
    glLinkProgram(orangeShaderProgram);

    // -------- Create Yellow Shader Program (Render Pipeline) ---------
    unsigned int yellowShaderProgram;
    yellowShaderProgram = glCreateProgram();
    glAttachShader(yellowShaderProgram, vertexShader.shaderId);
    glAttachShader(yellowShaderProgram, yellowShader.shaderId);
    glLinkProgram(yellowShaderProgram);

    unsigned int VAO_model;
    glGenVertexArrays(1, &VAO_model);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind the vertex array to avoid accidentally modifying it elsewhere
    glBindVertexArray(0);


    // While the User doesn't want to Quit (X Button, Alt+F4)
    while (!window.shouldClose()) // window -> window.window
    {
        window.processInput();

        // ^^^   window.processInput();
        red += 0.001f;
        if (red > 1)
            red -= 1;

        // render (paint the current frame of the game)
        glClearColor(red, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // DRY Principle
        // Don't Repeat Yourself
        glUseProgram(orangeShaderProgram);
        mesh1.render();

        glUseProgram(yellowShaderProgram);
        mesh2.render();

        window.present();
    }
    // Cleans up all the GLFW stuff
    glfwTerminate();
    return 0;
}