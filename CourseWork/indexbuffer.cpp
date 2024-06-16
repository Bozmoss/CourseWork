#include "indexbuffer.hpp"

// Constructor: Initializes the index buffer object
IndexBuffer::IndexBuffer() : m_number{ 0 } {
    // Generate a new buffer and store the handle in m_handle
    glGenBuffers(1, &m_handle);
    // Bind the buffer as an element array buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}

// Destructor: Cleans up the index buffer object
IndexBuffer::~IndexBuffer() {
    // If the buffer handle is valid, delete the buffer
    if (m_handle > 0) {
        glDeleteBuffers(1, &m_handle);
        m_handle = 0;  // Reset the handle to 0
    }
}

// Getter for m_handle: Returns the OpenGL handle of the index buffer
GLuint IndexBuffer::handle() const {
    return m_handle;
}

// Fills the index buffer with the provided indices
void IndexBuffer::fill(const std::vector<GLuint>& indices) {
    // Update the number of indices
    m_number = indices.size();
    // Bind the buffer as an element array buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
    // Upload the data to the buffer, specifying its usage pattern as static draw
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_number, indices.data(), GL_STATIC_DRAW);
}

// Getter for m_number: Returns the number of indices stored in the buffer
unsigned IndexBuffer::number() const {
    return m_number;
}
