#include <GL/glew.h>       // Include GLEW header for OpenGL extension loading
#include <GLFW/glfw3.h>    // Include GLFW header for creating windows and handling input
#include <iostream>        // Include for standard I/O
#include <vector>          // Include for using std::vector

#include "GLOBAL.hpp"      // Assuming this includes WINDOW_WIDTH and WINDOW_HEIGHT definitions
#include "filehandler.hpp" // Assuming this includes necessary file handling functionality
#include "shader.hpp"      // Assuming this includes Shader class definition
#include "program.hpp"     // Assuming this includes Program class definition
#include "vertexbuffer.hpp"// Assuming this includes VertexBuffer class definition
#include "indexbuffer.hpp" // Assuming this includes IndexBuffer class definition

float aY = 0, aX = 0, lastX, lastY;
bool firstMouse = true;

void mouse(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.01f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    aY += xoffset;
    aX -= yoffset;

    if (aX > 89.0f)
        aX = 89.0f;
    if (aX < -89.0f)
        aX = -89.0f;
}

int main() {
    // Initialize GLFW
    int hres = glfwInit();
    if (hres != 1) {
        std::cout << "Failed to initialise GLFW";
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "openGl", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetCursorPosCallback(window, mouse);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialise GLEW";
        glfwTerminate();
        return -1;
    }

    // Load vertex and fragment shaders
    Shader vertexShader(Shader::Type::VERTEX, "./vertex.glsl");
    if (vertexShader.inError()) {
        std::cout << vertexShader.error() << "\n";
    }
    Shader fragmentShader(Shader::Type::FRAGMENT, "./fragment.glsl");
    if (fragmentShader.inError()) {
        std::cout << fragmentShader.error() << "\n";
    }

    // Create and link shader program
    Program p;
    p.attachShader(vertexShader);
    p.attachShader(fragmentShader);
    p.activate();

    // Define vertex data for a triangle
    std::vector<GLfloat> verts = {
        -1.0f, -1.0f, // Bottom-left
         1.0f, -1.0f, // Bottom-right
        -1.0f,  1.0f, // Top-left
         1.0f,  1.0f  // Top-right
    };

    // Create and fill vertex buffer
    VertexBuffer vB;
    vB.fill(verts);

    // Define index data for a triangle
    std::vector<GLuint> indices = {
        0, 1, 2, 2, 1, 3  // Indices for the vertices of the triangle
    };

    // Create and fill index buffer
    IndexBuffer iB;
    iB.fill(indices);

    // Get location of the "vertexPosition" attribute in the shader program
    auto vertexPosition = glGetAttribLocation(p.handle(), "vertexPosition");
    glEnableVertexAttribArray(vertexPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vB.handle());
    glVertexAttribPointer(vertexPosition, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    auto i_resLocation = glGetUniformLocation(p.handle(), "i_res");
    auto aYLocation = glGetUniformLocation(p.handle(), "aY");
    auto aXLocation = glGetUniformLocation(p.handle(), "aX");

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        p.activate();

        glUniform3f(i_resLocation, WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f);
        glUniform1f(aYLocation, aY);
        glUniform1f(aXLocation, aX);

        // Draw the triangle using the index buffer
        glDrawElements(GL_TRIANGLES, iB.number(), GL_UNSIGNED_INT, nullptr);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    // Terminate GLFW and clean up resources
    glfwTerminate();
    return 0;
}