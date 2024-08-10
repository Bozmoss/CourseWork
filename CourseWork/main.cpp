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

#define PI 3.14159265359

float aX = 0, aY = 0, lastX, lastY, g = 0.00003, r = 0.8, f = 0.7;
bool firstMouse = true;
std::vector<Material> materials;
std::vector<Object> objects;

struct Point {
    float x;
    float y;
};

Point screenToNDC(float x, float y) {
    Point ndc;
    ndc.x = 2.0f * x / WINDOW_WIDTH - 1.0f;
    ndc.y = 1.0f - 2.0f * y / WINDOW_HEIGHT;
    return ndc;
}

float sphereSDF(float px, float py, float pz, float cx, float cy, float cz, float r) {
    return sqrt(
        (cx - px) * (cx - px) +
        (cy - py) * (cy - py) +
        (cz - pz) * (cz - pz)
    ) - r;
}

float torusSDF(float px, float py, float pz, float tx, float ty, int i) {
    float q[2] = { sqrt(px * px + pz * pz) - tx, py };
    return sqrt(q[0] * q[0] + q[1] * q[1]) - ty;

}

void mouse(GLFWwindow* window, double xpos, double ypos) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        for (Object& o : objects) {
            if (o.moving) {
                o.moving = false;
            }
        }
        firstMouse = true;
        return;
    }

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float sensitivity = 0.01f;

    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE) {
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
    else {
        Point pos = screenToNDC(xpos, ypos), last = screenToNDC(lastX, lastY);
        float xoffset = pos.x - last.x, yoffset = pos.y - last.y;
        xoffset *= sensitivity*100, yoffset *= sensitivity*100;
        if (abs(xoffset) < 0.001 && abs(yoffset) < 0.001) {
            xoffset = 0;
            yoffset = 0;
        }
        float finalT = 11.0;
        int finalIndex = -1;
        for (int i = 0; i < objects.size(); i++) {
            float t = 0.0;
            const float maxT = 10.0;
            while (t < maxT) {
                float p[3] = {
                    t * pos.x,
                    t * pos.y,
                    t * objects[i].z
                };
                float res = 0;
                switch (objects.at(i).type) {
                case 0:
                    res = sphereSDF(p[0], p[1], p[2], objects.at(i).x, objects.at(i).y ,objects.at(i).z, objects.at(i).l1);
                    break;
                case 1:
                    break; //TODO: ADD TORUS CAPABILITIES
                }
                if (res < 0.0001) {
                    break;
                }
                t += res;
            }
            if (t < finalT && t < maxT) {
                finalT = t;
                finalIndex = i;
            }
        }
        if (finalIndex != -1) {
            objects[finalIndex].moving = true;
            objects[finalIndex].dx = xoffset;
            objects[finalIndex].dy = yoffset;
        }
        for (Object& o : objects) {
            if (o.moving) {
                if (xoffset != 0 || yoffset != 0) {
                    o.dx = xoffset;
                    o.dy = yoffset;
                }
                else {
                    o.dx = 0;
                    o.dy = 0;
                }
            }
        }
        lastX = xpos;
        lastY = ypos;
    }
}

void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwDestroyWindow(window);
    }
}

void gravity() {
    for (Object& o : objects) {
        if (!o.moving) {
            if (o.down) {
                o.dy -= g;
                //o.y += o.dy;
                if (o.y - o.l1 < -1.5) {
                    o.y = -1.5 + o.l1;
                    o.dy = -o.dy * r;
                    if (abs(o.dy) < 0.000001) {
                        o.dy = 0.0;
                        o.down = false;
                    }
                }
            }
            else {
                o.dy -= g;
                //o.y += o.dy;
                if (o.dy <= 0) {
                    o.down = true;
                }
            }
        }
    }
}

void updateObjects() {
    for (Object& o : objects) {
        if (o.y - o.l1 <= -1.5 && !o.moving) {
            o.dx *= f;
        }
        o.x += o.dx;
        o.y += o.dy;
        o.z += o.dz;
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

    materials = {
        {1.0f, 0.0f, 0.0f, 0.2f, 0.7f, 0.5f, 0.4f, 32.0f},
        {0.0f, 1.0f, 0.0f, 0.2f, 0.7f, 0.5f, 0.0f, 32.0f},
        {0.0f, 0.0f, 1.0f, 0.2f, 0.7f, 0.5f, 0.0f, 16.0f}
    };

    objects = {
        {0, 0, -0.8, 0.0, 0.0, 0.5}, // {SDFtype, material, x, y, z, lengthVariable}
        {0, 1, 0.8, 0.0, 0.0, 0.3}
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

        gravity();

        updateObjects();

        fvs.update(p, aX, aY, materials, objects);

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