#pragma once

#include <GL/glew.h>       // Include GLEW header for OpenGL types and functions
#include <vector>          // Include vector for handling dynamic arrays

class IndexBuffer {
private:
    GLuint m_handle;       // OpenGL handle for the index buffer
    unsigned m_number;     // Number of indices stored in the buffer

public:
    // Constructor: initializes the index buffer object
    IndexBuffer();

    // Deleted copy constructor to prevent copying of IndexBuffer objects
    IndexBuffer(const IndexBuffer& other) = delete;

    // Deleted assignment operator to prevent assignment of IndexBuffer objects
    IndexBuffer operator=(const IndexBuffer& other) = delete;

    // Destructor: cleans up the index buffer object
    ~IndexBuffer();

    // Getter for m_handle: returns the OpenGL handle of the index buffer
    GLuint handle() const;

    // Fills the index buffer with the provided indices
    void fill(const std::vector<GLuint>& indices);

    // Getter for m_number: returns the number of indices stored in the buffer
    unsigned number() const;
};
