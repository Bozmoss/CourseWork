#pragma once

#include <GL/glew.h>       // Include GLEW header for OpenGL functionality
#include "filehandler.hpp" // Include filehandler.hpp for file handling utilities

class Shader {
private:
    GLint m_handle;         // OpenGL handle for the shader
    bool m_inError;         // Flag indicating if an error occurred during shader compilation
    std::string m_error;    // Error message if compilation fails

public:
    enum Type {
        VERTEX,             // Enum value for vertex shader
        FRAGMENT            // Enum value for fragment shader
    };

    // Constructor: loads and compiles a shader of specified type from the given file
    Shader(Type type, const char* fileName);

    // Deleted copy constructor to prevent copying of Shader objects
    Shader(const Shader& other) = delete;

    // Deleted assignment operator to prevent assignment of Shader objects
    Shader operator=(const Shader& other) = delete;

    // Destructor: cleans up the shader resources
    ~Shader();

    // Getter for m_handle: returns the OpenGL handle of the shader
    GLint handle() const;

    // Getter for m_inError: returns true if an error occurred during shader compilation
    bool inError() const;

    // Getter for m_error: returns the error message if compilation fails
    const std::string& error() const;
};
