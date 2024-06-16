#include "shader.hpp"       // Include the header file for Shader class
#include "filehandler.hpp"  // Include the header file for FileHandler class

Shader::Shader(Type type, const char* fileName)
    : m_handle{ 0 }, m_inError{ false }, m_error{ "" }
{
    // Determine the OpenGL shader type based on the Shader::Type enum
    GLenum glType = GL_VERTEX_SHADER;  // Default to vertex shader
    switch (type) {
    case VERTEX:
        glType = GL_VERTEX_SHADER;
        break;
    case FRAGMENT:
        glType = GL_FRAGMENT_SHADER;
        break;
    }

    // Create a new shader object of the specified type
    m_handle = glCreateShader(glType);

    // Read shader source code from file
    FileHandler fh(fileName);   // Create a FileHandler object with the provided fileName
    auto source = fh.readFile();  // Read file content into a string
    auto sourceChars = source.c_str();  // Get C-string (const char*) of the source code

    // Set the shader source code and compile the shader
    glShaderSource(m_handle, 1, &sourceChars, nullptr);
    glCompileShader(m_handle);

    // Check compilation status
    GLint status = GL_FALSE;
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        // Compilation failed, retrieve and store the error log
        const int bufferSize = 1024;  // Size of buffer for error log
        char buffer[bufferSize];      // Buffer to hold error log
        GLsizei length = 0;           // Length of the error log string

        // Retrieve the error log
        glGetShaderInfoLog(m_handle, bufferSize, &length, buffer);

        // Set error flags and store the error message
        m_inError = true;
        m_error = std::string(buffer, length);
    }
}

Shader::~Shader() {
    // Delete the shader object when Shader instance is destroyed
    if (m_handle > 0) {
        glDeleteShader(m_handle);
        m_handle = 0;
    }
}

GLint Shader::handle() const {
    // Return the OpenGL handle of the shader
    return m_handle;
}

bool Shader::inError() const {
    // Return true if an error occurred during shader compilation
    return m_inError;
}

const std::string& Shader::error() const {
    // Return the error message if shader compilation failed
    return m_error;
}
