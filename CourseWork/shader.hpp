/*****************************************************************//**
 * \file   shader.hpp
 * \brief  GLSL shader class
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/
#pragma once

#include <GL/glew.h>
#include "filehandler.hpp"

class Shader {
private:
    GLint m_handle;
    bool m_inError;
    std::string m_error;

public:
    enum Type {
        VERTEX,
        FRAGMENT
    };

    /**
     * Initialisation of the shader class
     * 
     * \param VERTEX or FRAGMENT type
     * \param char* fileName
     */
    Shader(Type type, const char* fileName);

    Shader(const Shader& other) = delete;

    Shader operator=(const Shader& other) = delete;

    ~Shader();

    /**
     * Returns the handle of the shader
     * 
     * \return GLint
     */
    GLint handle() const;

    /**
     * Determines if there has been an error
     * 
     * \return bool
     */
    bool inError() const;

    /**
     * Returns the error message
     * 
     * \return string
     */
    const std::string& error() const;
};
