#include "vertexbuffer.hpp"

// Constructor: Initializes the vertex buffer object
VertexBuffer::VertexBuffer() {
    // Generate a new buffer and store the handle in m_handle
    glGenBuffers(1, &m_handle);
    // Bind the buffer as an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
}

// Destructor: Cleans up the vertex buffer object
VertexBuffer::~VertexBuffer() {
    // If the buffer handle is valid, delete the buffer
    if (m_handle > 0) {
        glDeleteBuffers(1, &m_handle);
        m_handle = 0;  // Reset the handle to 0
    }
}

// Getter for m_handle: Returns the OpenGL handle of the vertex buffer
GLuint VertexBuffer::handle() const {
    return m_handle;
}

// Fills the vertex buffer with the provided data
void VertexBuffer::fill(const std::vector<GLfloat>& data) {
    // Bind the buffer as an array buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_handle);
    // Upload the data to the buffer, specifying its usage pattern as static draw
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * data.size(), data.data(), GL_STATIC_DRAW);
}
