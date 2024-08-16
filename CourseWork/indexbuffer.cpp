#include "indexbuffer.hpp"
IndexBuffer::IndexBuffer() : m_number{ 0 } {
    glGenBuffers(1, &m_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
}
IndexBuffer::~IndexBuffer() {
    if (m_handle > 0) {
        glDeleteBuffers(1, &m_handle);
        m_handle = 0;
    }
}
GLuint IndexBuffer::handle() const {
    return m_handle;
}
void IndexBuffer::fill(const std::vector<GLuint>& indices) {
    m_number = indices.size();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_number, indices.data(), GL_STATIC_DRAW);
}
unsigned IndexBuffer::number() const {
    return m_number;
}
