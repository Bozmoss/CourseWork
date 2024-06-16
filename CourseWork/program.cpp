#include "program.hpp"

// Constructor: Initializes the shader program object
Program::Program() {
    // Create a new shader program and store its handle in m_handle
    m_handle = glCreateProgram();
}

// Destructor: Cleans up the shader program object
Program::~Program() {
    // If the program handle is valid, delete the program
    if (m_handle > 0) {
        glDeleteProgram(m_handle);
        m_handle = 0;  // Reset the handle to 0
    }
}

// Getter for m_handle: Returns the OpenGL handle of the shader program
GLint Program::handle() const {
    return m_handle;
}

// Attaches a shader to the shader program
void Program::attachShader(const Shader& shader) {
    // Attach the shader to the program using its handle
    glAttachShader(m_handle, shader.handle());
}

// Detaches a shader from the shader program
void Program::detachShader(const Shader& shader) {
    // Detach the shader from the program using its handle
    glDetachShader(m_handle, shader.handle());
}

// Activates the shader program for use in rendering
void Program::activate() {
    // Link the shader program
    glLinkProgram(m_handle);

    // Check for linking errors
    GLint status;
    glGetProgramiv(m_handle, GL_LINK_STATUS, &status);
    if (status != GL_TRUE) {
        // If linking failed, retrieve the error log
        const int bufferSize = 1024;
        char buffer[bufferSize];
        GLsizei length = 0;
        glGetProgramInfoLog(m_handle, bufferSize, &length, buffer);
        std::cerr << "Program link error: " << std::string(buffer, length) << std::endl;
    }

    // Use the shader program
    glUseProgram(m_handle);
}
