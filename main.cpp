#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>

std::string LoadFile(std::string fileName) {
    std::string bufferStr, contentStr;
    std::fstream ifstr(fileName);
    
    if(!ifstr) {
        std::cout << "Error while loading file\n";
        exit(1);
    }
    
    while(!ifstr.eof()) {
        std::getline(ifstr, bufferStr);
        contentStr.append(bufferStr + "\n");
    }

    return contentStr;
}

GLuint CreateProgram(std::string vertexShaderPath, std::string fragmentShaderPath) {
    std::string vertexShaderStr, fragmentShaderStr;
    vertexShaderStr = LoadFile(vertexShaderPath);
    fragmentShaderStr = LoadFile(fragmentShaderPath);

    const char* ptrVertexShader = vertexShaderStr.c_str();
    const char* ptrFragmentShader = fragmentShaderStr.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(vertexShader, 1, &ptrVertexShader, NULL);
    glShaderSource(fragmentShader, 1, &ptrFragmentShader, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

int main() {
    glfwInit();

    GLFWwindow *window = glfwCreateWindow(200, 200, "title", 0, 0);

    glfwMakeContextCurrent(window);
    gladLoadGL();
    
    GLuint program = CreateProgram("", "");
    glUseProgram(program);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.2, 1);
            
        glfwSwapBuffers(window);
    }
}
