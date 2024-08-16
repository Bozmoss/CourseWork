/*****************************************************************//**
 * \file   material.hpp
 * \brief  Material structure
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/
#pragma once

/**
 * \param float r
 * \param float g
 * \param float b
 * \param float Ka
 * \param float Kd
 * \param float Ks
 * \param float Kr
 * \param float c
 */
struct Material {
    float r, g, b, Ka, Kd, Ks, Kr, c;
};