#include <GL/glew.h>            // OpenGL Extension Wrangler library
#include <GLFW/glfw3.h>         // OpenGL Framework library
#include <iostream>             // Terminal input-output library
#include <vector>               // Vector data structure library
#include <chrono>               // Time method library

#include "GLOBAL.hpp"           // Class with global variables
#include "filehandler.hpp"      // Class for file handling capabilities
#include "shader.hpp"           // Class for working with OpenGL shaders written in GLSL
#include "programH.hpp"         // Class for linking OpenGL shaders
#include "vertexbuffer.hpp"     // Class for graphics card communication regarding vertices of an OpenGL vertex shader
#include "indexbuffer.hpp"      // Class for graphics card communication regarding indices of the vertices of an OpenGL vertex shader
#include "fragvars.hpp"         // Class for handling variables in the OpenGL fragment shader
#include "material.hpp"         // Structure describing the material properties of an object
#include "object.hpp"           // Structure describing the physical location and states of a shape on the screen, and Object class

#define PI 3.14159265359

float aX = 0, aY = 0, lastX, lastY, g = 0.00003, r = 0.8, f = 0.7; // Rotation angles, mouse position, graity, coefficients of restitution and friction
bool firstMouse = true;                                            // Is mouse first moved
std::vector<Material> materials;
std::vector<Object> objects;

struct Point {
    float x;
    float y;
};

Point screenToNDC(float x, float y) { // Conversion of screen coordinates to a value between -1 and 1
    Point ndc;
    ndc.x = 2.0f * x / WINDOW_WIDTH - 1.0f;
    ndc.y = 1.0f - 2.0f * y / WINDOW_HEIGHT;
    return ndc;
}

float sphereSDF(float px, float py, float pz, float cx, float cy, float cz, float r) { // SDF for a sphere
    return sqrt(
        (cx - px) * (cx - px) +
        (cy - py) * (cy - py) +
        (cz - pz) * (cz - pz)
    ) - r;
}

float torusSDF(float px, float py, float pz, float tx, float ty, int i) { // SDF for a torus 
    float q[2] = { sqrt(px * px + pz * pz) - tx, py };
    return sqrt(q[0] * q[0] + q[1] * q[1]) - ty;

}

void mouse(GLFWwindow* window, double xpos, double ypos) {                    // All things relating to mouse actions
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) { // Stopping objects from unnecessarily moving if no mouse button is being pressed
        for (Object& o : objects) {
            o.stopMoving();
        }
        firstMouse = true;
        return;
    }

    if (firstMouse)                                                           // Setting initial click position to be correct
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float sensitivity = 0.01f;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {          // Getting roation angles based off mouse movement if CTRL is not being pressed
        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;
        lastX = xpos;
        lastY = ypos;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        aX += yoffset;
        aY -= xoffset;

        if (aX > PI / 4)
            aX = PI / 4;
        if (aX < -PI / 2)
            aX = -PI / 2;
    }
    else {                                                  // Calculating where to move and object if it is being dragged
        Point pos = screenToNDC(xpos, ypos);
        Point last = screenToNDC(lastX, lastY);
        float xoffset = pos.x - last.x;
        float yoffset = pos.y - last.y;
        xoffset *= sensitivity * 100;
        yoffset *= sensitivity * 100;
        if (abs(xoffset) < 0.001 && abs(yoffset) < 0.001) { // If the mouse is not moving, make sure the offsets are 0 rather than a small value
            xoffset = 0;
            yoffset = 0;
        }
        float finalT = 11.0;
        int finalIndex = -1;
        for (int i = 0; i < objects.size(); i++) {          // Raymarching
            if (objects.at(i).isClicked(pos.x, pos.y, objects.at(i).getData()->z, finalT)) {                   // Finding the closest object to the mouse
                finalT = objects.at(i).getLastT();
                finalIndex = i;
            }
        }
        if (finalIndex != -1) {
            objects.at(finalIndex).getData()->moving = true;
            objects.at(finalIndex).getData()->dx = xoffset;
            objects.at(finalIndex).getData()->dy = yoffset;
        }
        for (Object& o : objects) {                         // If the mouse is not moving, don't move the object
            if (o.getData()->moving) {
                if (xoffset != 0 || yoffset != 0) {
                    o.getData()->dx = xoffset;
                    o.getData()->dy = yoffset;
                }
                else {
                    o.getData()->dx = 0;
                    o.getData()->dy = 0;
                }
            }
        }
        lastX = xpos;
        lastY = ypos;
    }
}

void key(GLFWwindow* window, int key, int scancode, int action, int mods) { // If user presses ESC, close
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwDestroyWindow(window);
    }
}

void gravity() {                                // Handling acceleration and bouncing due to gravity
    for (Object& o : objects) {
        o.applyGravity(g, r);
    }
}

void updateObjectDatas() {                         // Moving objects according to their dx, dy and dz
    for (Object& o : objects) {
        o.update(f);
    }
}

int main(int argc, char** argv) {                                                                              // Main method
    int hres = glfwInit();                                                                                     // Initialising GLFW
    if (hres != 1) {
        std::cout << "Failed to initialise GLFW";
        return -1;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());                                       // Getting screen info

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OpenGL", glfwGetPrimaryMonitor(), NULL); // Creating window
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key);
    glfwSetCursorPosCallback(window, mouse);

    if (glewInit() != GLEW_OK) {                                                                               // Initialising GLEW
        std::cout << "Failed to initialise GLEW";
        glfwTerminate();
        return -1;
    }

    Shader vertexShader(Shader::Type::VERTEX, "./vertex.glsl");                                                // Load vertex and fragment shaders
    if (vertexShader.inError()) {
        std::cout << vertexShader.error() << "\n";
    }
    Shader fragmentShader(Shader::Type::FRAGMENT, "./fragment.glsl"); // Main run mode
    //Shader fragmentShader(Shader::Type::FRAGMENT, "./debugFrag.glsl");  // Debug run mode
    if (fragmentShader.inError()) {
        std::cout << fragmentShader.error() << "\n";
    }

    Program p;                                                                                                 // Create and link shader program
    p.attachShader(vertexShader);
    p.attachShader(fragmentShader);
    p.activate();

    std::vector<float> res = { WINDOW_WIDTH, WINDOW_HEIGHT, 1.0f };                                            // Window data
    std::vector<std::vector<float>> lights = {                                                                 // Light positions
        {2.0, 0.6, 1.0},
        {-2.0, 0.6, 1.0},
        {0.0, 0.8, 1.0}
    };
    std::vector<std::vector<float>> lightCols = {                                                              // Light colours
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0},
        {1.0, 1.0, 1.0}
    };

    materials = {                                                                                              // Material data
        {1.0f, 0.0f, 0.0f, 0.2f, 0.7f, 0.5f, 0.4f, 32.0f},
        {0.0f, 1.0f, 0.0f, 0.2f, 0.7f, 0.5f, 0.0f, 32.0f},
        {0.0f, 0.0f, 1.0f, 0.2f, 0.7f, 0.5f, 0.0f, 16.0f}
    };

    ObjectData objectDatas[] = {                                                                              // ObjectData data
        {0, 0, -0.8, 0.0, 0.0, 0.5},                                                                           // {SDFtype, material, x, y, z, lengthVariable}
        {0, 1, 0.8, 0.0, 0.0, 0.3}
    };

    for (int i = 0; i < sizeof(objectDatas) / sizeof(objectDatas[0]); i++) {
        switch (objectDatas[i].type) {
        case 0:
            objects.push_back(Sphere(objectDatas[i]));
            break;
        }
    }

    FragVars fvs(res, aX, aY, lights, lightCols, materials, objects);

    std::vector<GLfloat> verts = {                                                                             // Define vertex data for a triangle
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f
    };

    VertexBuffer vB;                                                                                           // Create and fill vertex buffer
    vB.fill(verts);

    std::vector<GLuint> indices = {                                                                            // Define index data for a triangle
        0, 1, 2, 2, 1, 3
    };

    IndexBuffer iB;                                                                                            // Create and fill index buffer
    iB.fill(indices);

    auto vertexPosition = glGetAttribLocation(p.handle(), "vertexPosition");                                   // Get location of the "vertexPosition" attribute
    glEnableVertexAttribArray(vertexPosition);                                                                 // in the shader program
    glBindBuffer(GL_ARRAY_BUFFER, vB.handle());
    glVertexAttribPointer(vertexPosition, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    fvs.init(p);                                                                                               // Start the program

    auto startTime = std::chrono::high_resolution_clock::now();                                                // Start the clock

    while (!glfwWindowShouldClose(window)) {                                 // Rendering loop
        glClear(GL_COLOR_BUFFER_BIT);                                        // Clear the color buffer

        p.activate();

        gravity();

        updateObjectDatas();

        fvs.update(p, aX, aY, materials, objects);

        glDrawElements(GL_TRIANGLES, iB.number(), GL_UNSIGNED_INT, nullptr); // Draw the triangle using the index buffer

        glfwSwapBuffers(window);                                             // Swap front and back buffers

        glfwPollEvents();                                                    // Poll for and process events
    }

    glfwTerminate(); // Terminate GLFW and clean up resources
    return 0;
}