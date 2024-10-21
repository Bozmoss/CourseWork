#pragma once

#include "imgui.h"

class GUI {
private:
    int width, height;
public:
    GUI(int width, int height);
    void mainMenu(int& screen);
};
