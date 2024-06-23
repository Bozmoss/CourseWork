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

void UniformBuffer::fill(const std::vector<Material>& data, Program &p) {
    m_number = data.size();
    glBindBuffer(GL_UNIFORM_BUFFER, m_handle);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Material) * m_number, data.data(), GL_STATIC_DRAW);
    GLuint materialBlockIndex = glGetUniformBlockIndex(p.handle(), "MaterialBlock");
    glUniformBlockBinding(p.handle(), materialBlockIndex, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}