/*****************************************************************//**
 * \file   programH.hpp
 * \brief  Shader link program
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/
#pragma once

#include <GL/glew.h>
#include "shader.hpp"

class Program {
private:
    GLint m_handle;

public:
    /**
     * Initialisation of the program class
     * 
     */
    Program();

    Program(const Program& other) = delete;

    Program operator=(const Program& other) = delete;

    ~Program();

    /**
     * Returns the handle of the program
     * 
     * \return GLint
     */
    GLint handle() const;

    /**
     * Attaches a shader
     * 
     * \param Shader shader
     */
    void attachShader(const Shader& shader);

    /**
     * Detaches a shader
     * 
     * \param Shader shader
     */
    void detachShader(const Shader& shader);

    /**
     * Starts the program
     * 
     */
    void activate();
};
