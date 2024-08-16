/*****************************************************************//**
 * \file   vertexbuffer.hpp
 * \brief  Buffer for vertices
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/
#pragma once

#include <vector>
#include <GL/glew.h>

class VertexBuffer {
private:
    GLuint m_handle;

public:
    /**
     * Initialisation of the vertex buffer class
     * 
     */
    VertexBuffer();

    VertexBuffer(const VertexBuffer& other) = delete;

    VertexBuffer operator=(const VertexBuffer& other) = delete;

    ~VertexBuffer();

    /**
     * Returns the handle of the buffer
     * 
     * \return GLuint
     */
    GLuint handle() const;

    /**
     * Fills the buffer with data
     * 
     * \param vector<GLfloat> data
     */
    void fill(const std::vector<GLfloat>& data);
};
