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
#include <memory>
#include <chrono>
#include <cstdlib>

#include "GLOBAL.hpp"
#include "filehandler.hpp"
#include "shader.hpp"
#include "programH.hpp"
#include "vertexbuffer.hpp"
#include "indexbuffer.hpp"
#include "fragvars.hpp"
#include "material.hpp"
#include "object.hpp"
#include "game.hpp"
#include "vec.hpp"

std::vector<Material> materials;
std::vector<std::shared_ptr<Object>> objects;
Game game(objects);
const float g = 0.00003, r = 0.8, f = 0.7;

void mouse(GLFWwindow* window, double xpos, double ypos) {
    game.mouseEvent(window, xpos, ypos, g, r);
}

void key(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwDestroyWindow(window);
    }
    if (key == GLFW_KEY_R && action == GLFW_PRESS) {
        objects.clear();
        int r[4] = { rand() % 100, rand() % 100, rand() % 100, rand() % 100 };
        ObjectData objectDatas[] = {
            {0, 0, vec {r[0] / 100.0f, 1.5, r[1] / 100.0f}, 0.5, 1.0},
            {0, 1, vec {r[2] / 100.0f, 0.5, r[3] / 100.0f}, 0.4, 1.0}
        };
        for (int i = 0; i < sizeof(objectDatas) / sizeof(objectDatas[0]); i++) {
            switch (objectDatas[i].type) {
            case 0:
                auto s = std::make_shared<Sphere>(objectDatas[i]);
                objects.push_back(s);
                break;
            }
        }
    }
}

void update() {
    for (auto& o : objects) {
        o->updateObject(g, r);
    }

    int i = 0;
    for (auto& o : objects) {
        for (int j = i + 1; j < objects.size(); j++) {
            if (o->checkCollision((*objects.at(j)))) {
                o->resolveCollision((*objects.at(j)));
            }
        }
        i++;
    }
}

void updateObjectDatas() {
    for (auto& o : objects) {
        o->update(f);
    }
}

int main(int argc, char** argv) {
    srand((unsigned)time(NULL));
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
    glfwWindowHint(GLFW_SAMPLES, 4);

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

    int r[4] = { rand() % 100, rand() % 100, rand() % 100, rand() % 100 };

    ObjectData objectDatas[] = {
        {0, 0, vec {r[0] / 100.0f, 1.5, r[1] / 100.0f}, 0.5, 1.0},
        {0, 1, vec {r[2] / 100.0f, 0.5, r[3] / 100.0f}, 0.4, 1.0}
    };

    for (int i = 0; i < sizeof(objectDatas) / sizeof(objectDatas[0]); i++) {
        switch (objectDatas[i].type) {
        case 0:
            auto s = std::make_shared<Sphere>(objectDatas[i]);
            objects.push_back(s);
            break;
        }
    }

    FragVars fvs(res, game.getAX(), game.getAY(), lights, lightCols, materials, objects);

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        p.activate();

        update();

        updateObjectDatas();

        game.updateObjects(objects);

        fvs.update(p, game.getAX(), game.getAY(), materials ,objects);

        glDrawElements(GL_TRIANGLES, iB.number(), GL_UNSIGNED_INT, nullptr);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}