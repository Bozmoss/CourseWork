#pragma once

#include <GL/glew.h>       // Include GLEW header for OpenGL types and functions
#include "shader.hpp"      // Include header for the Shader class

class Program {
private:
    GLint m_handle;        // OpenGL handle for the shader program

public:
    // Constructor: initializes the shader program object
    Program();

    // Deleted copy constructor to prevent copying of Program objects
    Program(const Program& other) = delete;

    // Deleted assignment operator to prevent assignment of Program objects
    Program operator=(const Program& other) = delete;

    // Destructor: cleans up the shader program object
    ~Program();

    // Getter for m_handle: returns the OpenGL handle of the shader program
    GLint handle() const;

    // Attaches a shader to the shader program
    void attachShader(const Shader& shader);

    // Detaches a shader from the shader program
    void detachShader(const Shader& shader);

    // Activates the shader program for use in rendering
    void activate();
};
