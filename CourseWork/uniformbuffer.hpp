#pragma once

#include <GL/glew.h>
#include <vector>
#include <string>

#include "program.hpp"
#include "object.hpp"
#include "material.hpp"

template <typename T> class UniformBuffer {
private:
    T* ptr;
    GLuint m_handle;
    unsigned m_number;
public:
    UniformBuffer();

    UniformBuffer(const UniformBuffer& other) = delete;

    UniformBuffer operator=(const UniformBuffer& other) = delete;

    ~UniformBuffer();

    GLuint handle() const;

    void fill(const std::vector<T>& data, Program &p, const GLchar *name);
};
