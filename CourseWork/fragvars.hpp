#pragma once

#include <GL/glew.h>         // OpenGL Extension Wrangler library
#include <vector>            // Vector data structure library
#include <chrono>            // Time method library

#include "material.hpp"      // Structure describing the material properties of an object
#include "object.hpp"        // Structure describing the physical location and states of a shape on the screen
#include "programH.hpp"      // Class for linking OpenGL shaders
#include "uniformbuffer.hpp" // Class for graphics card communication regarding uniform buffer blocks in an OpenGL fragment shader

class FragVars {
private:
    std::vector<float> res;                                                                        // Screen resolution
    float aX, aY;                                                                                  // Rotation angles
    std::vector<std::vector<float>> lights, lightCols;                                             // Light positions and colours
    std::vector<Material> materials;
    std::vector<Object> objects;
    std::chrono::steady_clock::time_point time;                                                    // Used for elapsed time
    GLint resLocation, aYLocation, aXLocation, timeLocation, lightsLocation, lightColsLocation,
        materialsLocation, objectsLocation, lightsLLocation, materialsLLocation, objectsLLocation; // Location in fragment shader of given variables
    UniformBuffer ub;

    void materialObjectDataUpdate(Program& p);                                                         // Update the material and object arrays to pass to the uniform buffer
public:
    FragVars(std::vector<float>& res, float& aX, float& aY, std::vector<std::vector<float>>& lights,
        std::vector<std::vector<float>>& lightCols, std::vector<Material>& materials, std::vector<Object>& objects); // Initialises FragVars with all the required variables

    void init(Program &p);                                                                                           // Setup of variables

    void update(Program& p, float &aX, float &aY, std::vector<Material> materials, std::vector<Object> objects);     // Update when something changes
};