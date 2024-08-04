#include <GL/glew.h>       // Include GLEW header for OpenGL extension loading
#include <GLFW/glfw3.h>    // Include GLFW header for creating windows and handling input
#include <iostream>        // Include for standard I/O
#include <vector>          // Include for using std::vector
#include <chrono>

#include "GLOBAL.hpp"      // Assuming this includes WINDOW_WIDTH and WINDOW_HEIGHT definitions
#include "filehandler.hpp" // Assuming this includes necessary file handling functionality
#include "shader.hpp"      // Assuming this includes Shader class definition
#include "programH.hpp"     // Assuming this includes Program class definition
#include "vertexbuffer.hpp"// Assuming this includes VertexBuffer class definition
#include "indexbuffer.hpp" // Assuming this includes IndexBuffer class definition
#include "fragvars.hpp"
#include "material.hpp"

float aX = 0, aY = 0, lastX, lastY;
bool firstMouse = true;

void mouse(GLFWwindow* window, double xpos, double ypos) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        firstMouse = true;
        return;
    }
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

    aX -= yoffset;
    aY += xoffset;

    if (aX > 89.0f)
        aX = 89.0f;
    if (aX < -89.0f)
        aX = -89.0f;
}

void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwDestroyWindow(window);
    }
}

int main(int argc, char** argv) {
    // Initialize GLFW
    int hres = glfwInit();
    if (hres != 1) {
        std::cout << "Failed to initialise GLFW";
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OpenGL", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key);
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
    Shader fragmentShader(Shader::Type::FRAGMENT, "./fragment.glsl"); // Main run mode
    //Shader fragmentShader(Shader::Type::FRAGMENT, "./debugFrag.glsl");  // Debug run mode
    if (fragmentShader.inError()) {
        std::cout << fragmentShader.error() << "\n";
    }

    // Create and link shader program
    Program p;
    p.attachShader(vertexShader);
    p.attachShader(fragmentShader);
    p.activate();

    std::vector<float> res = { WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f };
    std::vector<std::vector<float>> lights = {
        {2.0, 0.6, 1.0},
        {-2.0, 0.6, 1.0},
        {0.0, 0.8, 1.0}
    };
    std::vector<std::vector<float>> lightCols = {
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0}
    };

    std::vector<Material> materials = {
        {1.0f, 0.0f, 0.0f, 0.2f, 0.7f, 0.5f, 0.4f, 32.0f},
        {0.0f, 1.0f, 0.0f, 0.2f, 0.7f, 0.5f, 0.0f, 32.0f},
        {0.0f, 0.0f, 1.0f, 0.2f, 0.7f, 0.5f, 0.0f, 16.0f}
    };

    std::vector<Object> objects = {
        {0, 1, 0.9, 0.0, 0.0, 0.2}, // {SDFtype, material, x, y, z, lengthVariable}
        {0, 0, 0.0, 0.0, 0.0, 0.5},
    };
    FragVars fvs(res, aX, aY, lights, lightCols, materials, objects);

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

    fvs.init(p);

    auto startTime = std::chrono::high_resolution_clock::now();

    // Rendering loop
    while (!glfwWindowShouldClose(window)) {
        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

        p.activate();

        fvs.update(aX, aY);

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