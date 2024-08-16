/*****************************************************************//**
 * \file   main.cpp
 * \brief  3D rendering engine
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>

#include "GLOBAL.hpp"
#include "filehandler.hpp"
#include "shader.hpp"
#include "programH.hpp"
#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include "fragvars.hpp"
#include "material.hpp"
#include "object.hpp"

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
            o.stopMoving();
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
        Point pos = screenToNDC(xpos, ypos);
        Point last = screenToNDC(lastX, lastY);
        float xoffset = pos.x - last.x;
        float yoffset = pos.y - last.y;
        xoffset *= sensitivity * 100;
        yoffset *= sensitivity * 100;
        if (abs(xoffset) < 0.001 && abs(yoffset) < 0.001) {
            xoffset = 0;
            yoffset = 0;
        }
        float finalT = 11.0;
        int finalIndex = -1;
        for (int i = 0; i < objects.size(); i++) {
            if (objects.at(i).isClicked(pos.x, pos.y, objects.at(i).getData()->z, finalT)) {
                finalT = objects.at(i).getLastT();
                finalIndex = i;
            }
        }
        if (finalIndex != -1) {
            objects.at(finalIndex).getData()->moving = true;
            objects.at(finalIndex).getData()->dx = xoffset;
            objects.at(finalIndex).getData()->dy = yoffset;
        }
        for (Object& o : objects) {
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

void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwDestroyWindow(window);
    }
}

void gravity() {
    for (Object& o : objects) {
        o.applyGravity(g, r);
    }
}

void updateObjectDatas() {
    for (Object& o : objects) {
        o.update(f);
    }
}

int main(int argc, char** argv) {
    int hres = glfwInit();
    if (hres != 1) {
        std::cout << "Failed to initialise GLFW";
        return -1;
    }

    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "OpenGL", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key);
    glfwSetCursorPosCallback(window, mouse);

    if (glewInit() != GLEW_OK) {
        std::cout << "Failed to initialise GLEW";
        glfwTerminate();
        return -1;
    }

    Shader vertexShader(Shader::Type::VERTEX, "./vertex.glsl");
    if (vertexShader.inError()) {
        std::cout << vertexShader.error() << "\n";
    }
    Shader fragmentShader(Shader::Type::FRAGMENT, "./fragment.glsl");
    if (fragmentShader.inError()) {
        std::cout << fragmentShader.error() << "\n";
    }

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

    ObjectData objectDatas[] = {
        {0, 0, -0.8, 0.0, 0.0, 0.5},
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

    std::vector<GLfloat> verts = {
        -1.0f, -1.0f,
         1.0f, -1.0f,
        -1.0f,  1.0f,
         1.0f,  1.0f
    };

    VertexBuffer vB;
    vB.fill(verts);

    std::vector<GLuint> indices = {
        0, 1, 2, 2, 1, 3
    };

    IndexBuffer iB;
    iB.fill(indices);

    auto vertexPosition = glGetAttribLocation(p.handle(), "vertexPosition");
    glEnableVertexAttribArray(vertexPosition);
    glBindBuffer(GL_ARRAY_BUFFER, vB.handle());
    glVertexAttribPointer(vertexPosition, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    fvs.init(p);

    auto startTime = std::chrono::high_resolution_clock::now();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        p.activate();

        gravity();

        updateObjectDatas();

        fvs.update(p, aX, aY, materials, objects);

        glDrawElements(GL_TRIANGLES, iB.number(), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}