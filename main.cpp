#include "include/glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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
    
    GLuint program = CreateProgram("shader.frag", "shader.vert");
    glUseProgram(program);
    
    GLuint vbo {};
    glCreateBuffers(1, &vbo);

    float pos[] = {
    -1, -1, 1,
    0, 1, 1,
    1, -1, 1,
    };

    glNamedBufferStorage(vbo, sizeof(pos), pos, 0);
    
    GLuint vao {};
    glCreateVertexArrays(1, &vao);
    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(float) * 3);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribFormat(vao, 0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
    glEnableVertexArrayAttrib(vao, 0);

    while(!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.1, 0.1, 0.2, 1);
           
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }
}
