#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <loader.hpp>

using namespace glm;

const std::string VERTEX = "shaders/shader.vert";
const std::string FRAG = "shaders/shader.frag";

void draw1();
void draw2();

int main()
{
    glfwInit();

    GLFWwindow *window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow(1024, 768, "Temp_01", NULL, NULL);
    glfwMakeContextCurrent(window); // Initialize GLEW

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    GLuint programID = LoadShader(VERTEX.c_str(), FRAG.c_str());

    
    glUseProgram(programID);



    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0., 0., 0., 0.);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        GLint uniformLocation = glGetUniformLocation(programID, "iTime");

        float timeValue = glfwGetTime();

        std::cout << timeValue << std::endl;
        glUniform1f(uniformLocation, timeValue);

        uniformLocation = glGetUniformLocation(programID, "iResolution");
        glUniform2f(uniformLocation, 1024., 768.);
        
        draw1();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void draw1() {
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        -1.0f,  1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,
    };

    static const GLfloat g_vertex_buffer_data2[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f,  -1.0f, 0.0f,
    };

        // This will identify our vertex buffer
    GLuint vertexbuffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // 1st attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data2), g_vertex_buffer_data2, GL_STATIC_DRAW);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}