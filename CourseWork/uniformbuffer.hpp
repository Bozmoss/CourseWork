#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>

#include "programH.hpp"
#include "object.hpp"
#include "material.hpp"

class UniformBuffer {
private:
    GLuint m_handle;
    unsigned m_number;
public:
    UniformBuffer();

    UniformBuffer(const UniformBuffer& other) = delete;

    UniformBuffer operator=(const UniformBuffer& other) = delete;

    ~UniformBuffer();

    GLuint handle() const;

    template <typename T>
    void fill(const std::vector<T>& data, Program& p, const GLchar* name) {
        m_number = data.size();
        glBindBuffer(GL_UNIFORM_BUFFER, m_handle);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(T) * m_number, data.data(), GL_STATIC_DRAW);
        GLuint blockIndex = glGetUniformBlockIndex(p.handle(), name);
        glUniformBlockBinding(p.handle(), blockIndex, 0);
        glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_handle);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
    }
};
