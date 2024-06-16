#pragma once

#include <vector>          // Include vector for handling dynamic arrays
#include <GL/glew.h>       // Include GLEW header for OpenGL types and functions

class VertexBuffer {
private:
    GLuint m_handle;       // OpenGL handle for the vertex buffer

public:
    // Constructor: initializes the vertex buffer object
    VertexBuffer();

    // Deleted copy constructor to prevent copying of VertexBuffer objects
    VertexBuffer(const VertexBuffer& other) = delete;

    // Deleted assignment operator to prevent assignment of VertexBuffer objects
    VertexBuffer operator=(const VertexBuffer& other) = delete;

    // Destructor: cleans up the vertex buffer object
    ~VertexBuffer();

    // Getter for m_handle: returns the OpenGL handle of the vertex buffer
    GLuint handle() const;

    // Fills the vertex buffer with the provided data
    void fill(const std::vector<GLfloat>& data);
};
