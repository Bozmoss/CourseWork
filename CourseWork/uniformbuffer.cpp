#include "uniformbuffer.hpp"

template <typename T> UniformBuffer<T>::UniformBuffer() : m_number{ 0 } {
    glGenBuffers(1, &m_handle);
}

template <typename T> UniformBuffer<T>::~UniformBuffer() {
    if (m_handle > 0) {
        glDeleteBuffers(1, &m_handle);
        m_handle = 0;
    }
}

template <typename T> GLuint UniformBuffer<T>::handle() const {
    return m_handle;
}

template <typename T> void UniformBuffer<T>::fill(const std::vector<T>& data, Program& p, const GLchar *name) {
    m_number = data.size();
    glBindBuffer(GL_UNIFORM_BUFFER, m_handle);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(T) * m_number, data.data(), GL_STATIC_DRAW);
    GLuint blockIndex = glGetUniformBlockIndex(p.handle(), name);
    glUniformBlockBinding(p.handle(), blockIndex, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}