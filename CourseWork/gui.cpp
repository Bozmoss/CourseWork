#include "gui.hpp"

using namespace ImGui;

GUI::GUI(int width, int height) :
    width {width}, height {height} {}

void GUI::mainMenu(int& screen) {
    SetNextWindowPos(ImVec2(width / 2 - width / 10.0, height / 2 - height / 10.0));
    SetNextWindowSize(ImVec2(width / 5.0, height / 5.0));
    Begin("Main Menu");
    Text("Select one of the options to either make a new file, \nor load a file");
    if (Button("New")) {
        screen++;
    }
    SameLine();
    if (Button("Load")) {
        
    }
    End();
}
