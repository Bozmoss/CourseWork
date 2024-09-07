/*****************************************************************//**
 * \file   game.hpp
 * \brief  Game control elements
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/

#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <memory>

#include "GLOBAL.hpp"
#include "object.hpp"

class Game {
private:

    struct Point {
        float x, y;
    };

    float aX = 0, aY = 0, lastX, lastY, g = 0.00003, r = 0.8, f = 0.7;
    bool firstMouse = true;
    std::vector<std::shared_ptr<Object>> objects;

    Point screenToNDC(float x, float y);

    void drawRay(std::vector<float> ro, std::vector<float> rd, float distance);

public:

    Game(std::vector<std::shared_ptr<Object>> &objects);

    void mouseEvent(GLFWwindow* window, double xpos, double ypos);

    void updateObjects(std::vector<std::shared_ptr<Object>>& objects);

    float getAX(), getAY();
};
