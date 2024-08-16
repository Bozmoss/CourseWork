/*****************************************************************//**
 * \file   indexbuffer.hpp
 * \brief  Buffer for vertex indices
 * 
 * \author Ben
 * \date   August 2024
 *********************************************************************/
#pragma once

#include <GL/glew.h>
#include <vector>

class IndexBuffer {
private:
    GLuint m_handle;
    unsigned m_number;

public:
    /**
     * Initialisation of the index buffer class
     * 
     */
    IndexBuffer();

    IndexBuffer(const IndexBuffer& other) = delete;

    IndexBuffer operator=(const IndexBuffer& other) = delete;

    ~IndexBuffer();

    /**
     * Returns the handle of the buffer
     * 
     * \return GLuint
     */
    GLuint handle() const;

    /**
     * Fills the buffer
     * 
     * \param vector<GLuint> indices
     */
    void fill(const std::vector<GLuint>& indices);

    /**
     * Returns the number of indices
     * 
     * \return unsigned
     */
    unsigned number() const;
};
