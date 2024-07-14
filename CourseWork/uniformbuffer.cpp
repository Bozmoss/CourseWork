#include "uniformbuffer.hpp"

UniformBuffer::UniformBuffer() : m_number{ 0 } {
    glGenBuffers(1, &m_handle);
}

UniformBuffer::~UniformBuffer() {
    if (m_handle > 0) {
        glDeleteBuffers(1, &m_handle);
        m_handle = 0;
    }
}

GLuint UniformBuffer::handle() const {
    return m_handle;
}