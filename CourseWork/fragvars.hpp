/*****************************************************************//**
 * \file   fragvars.hpp
 * \brief  Fragment shader variable handler
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/
#pragma once

#include <GL/glew.h>
#include <vector>
#include <chrono>
#include <memory>

#include "material.hpp"
#include "object.hpp"
#include "programH.hpp"
#include "uniformbuffer.hpp"

class FragVars {
private:
    std::vector<float> res;
    float aX, aY;
    std::vector<std::vector<float>> lights, lightCols;
    std::vector<Material> materials;
    std::vector<std::shared_ptr<Object>> objects;
    std::chrono::steady_clock::time_point time;
    GLint resLocation, aYLocation, aXLocation, timeLocation, lightsLocation, lightColsLocation,
        materialsLocation, objectsLocation, lightsLLocation, materialsLLocation, objectsLLocation;
    UniformBuffer ub;

    /**
     * Updates material and object data
     * 
     * \param Program p
     */
    void materialObjectDataUpdate(Program& p);
public:
    /**
     * Initialises the fragment variable handler class
     * 
     * \param vector<float> res
     * \param float aX
     * \param float aY
     * \param vector<vector<flaot>> lights
     * \param vector<vector<float>> lightCols
     * \param vector<Material> materials
     * \param vector<Object> objects
     */
    FragVars(std::vector<float>& res, float aX, float aY, std::vector<std::vector<float>>& lights,
        std::vector<std::vector<float>>& lightCols, std::vector<Material>& materials, std::vector<std::shared_ptr<Object>>& objects);

    /**
     * Initial update of data
     * 
     * \param Program p
     */
    void init(Program &p);

    /**
     * Update of data
     * 
     * \param Program p
     * \param float aX
     * \param float aY
     * \param vector<Material> materials
     * \param vector<Object> objects
     */
    void update(Program& p, const float &aX, const float &aY, std::vector<Material> materials, std::vector<std::shared_ptr<Object>>& objects);
};