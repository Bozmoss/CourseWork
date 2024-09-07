#include "game.hpp"

#include <iostream>

Game::Point Game::screenToNDC(float x, float y) {
    Point ndc;
    ndc.x = 2.0f * x / WINDOW_WIDTH - 1.0f;
    ndc.y = 1.0f - 2.0f * y / WINDOW_HEIGHT;
    return ndc;
}

void Game::drawRay(std::vector<float> ro, std::vector<float> rd, float distance) {
    std::vector<float> p = {
            ro.at(0) + distance * rd.at(0),
            ro.at(1) + distance * rd.at(1),
            ro.at(2) + distance * rd.at(2)
    };
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(ro.at(0), ro.at(1), ro.at(2));
    glVertex3f(p.at(0), p.at(1), p.at(2));
    glEnd();
}

Game::Game(std::vector<std::shared_ptr<Object>> &objects):
    objects { objects } {}

void Game::mouseEvent(GLFWwindow* window, double xpos, double ypos) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        for (auto& o : objects) {
            o->stopMoving();
            o->reset();
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

        std::vector<float> posStart = {
            cos(aY) * pos.x - sin(aY),
            sin(aX) * sin(aY) * pos.x + cos(aX) * pos.y + sin(aX) * cos(aY),
            -sin(aY) * cos(aX) * pos.x + sin(aX) * pos.y - cos(aX) * cos(aY)
        };
        std::vector<float> posEnd = {
            cos(aY)* pos.x + sin(aY),
            sin(aX)* sin(aY)* pos.x + cos(aX) * pos.y - sin(aX) * cos(aY),
            -sin(aY) * cos(aX) * pos.x + sin(aX) * pos.y + cos(aX) * cos(aY)
        };

        float mag = sqrt((posEnd[0] - posStart[0]) * (posEnd[0] - posStart[0]) +
            (posEnd[1] - posStart[1]) * (posEnd[1] - posStart[1]) +
            (posEnd[2] - posStart[2]) * (posEnd[2] - posStart[2]));

        std::vector<float> posRd = {
            (posEnd[0] - posStart[0]) / mag,
            (posEnd[1] - posStart[1]) / mag,
            (posEnd[2] - posStart[2]) / mag
        };

        drawRay(posStart, posRd, 100.0f);

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
        int i = 0;
        for (auto& o : objects) {
            if (o->isClicked(posStart, posRd, finalT)) {
                finalT = o->getLastT();
                finalIndex = i;
            }
            i++;
        }
        if (finalIndex != -1) {
            objects.at(finalIndex)->getData()->moving = true;
            objects.at(finalIndex)->getData()->dx = xoffset;
            objects.at(finalIndex)->getData()->dy = yoffset;
        }
        for (auto& o : objects) {
            if (o->getData()->moving) {
                if (xoffset != 0 || yoffset != 0) {
                    o->getData()->dx = xoffset;
                    o->getData()->dy = yoffset;
                }
                else {
                    o->getData()->dx = 0;
                    o->getData()->dy = 0;
                }
            }
            else {
                o->getData()->dx = 0;
                o->getData()->dy = 0;
            }
        }
        lastX = xpos;
        lastY = ypos;
    }
}

void Game::updateObjects(std::vector<std::shared_ptr<Object>>& objects) {
    this->objects = objects;
}

float Game::getAX() {
    return aX;
}

float Game::getAY() {
    return aY;
}