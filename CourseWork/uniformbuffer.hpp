#pragma once

#include <GL/glew.h>
#include <vector>

#include "program.hpp"
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

    void fill(const std::vector<Material>& data, Program &p);
};
