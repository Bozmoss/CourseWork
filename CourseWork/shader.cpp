#include "shader.hpp"
#include "filehandler.hpp"

Shader::Shader(Type type, const char* fileName)
    : m_handle{ 0 }, m_inError{ false }, m_error{ "" }
{
    GLenum glType = GL_VERTEX_SHADER;
    switch (type) {
    case VERTEX:
        glType = GL_VERTEX_SHADER;
        break;
    case FRAGMENT:
        glType = GL_FRAGMENT_SHADER;
        break;
    }
    m_handle = glCreateShader(glType);
    FileHandler fh(fileName);
    auto source = fh.readFile();
    auto sourceChars = source.c_str();
    glShaderSource(m_handle, 1, &sourceChars, nullptr);
    glCompileShader(m_handle);
    GLint status = GL_FALSE;
    glGetShaderiv(m_handle, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE) {
        const int bufferSize = 1024;
        char buffer[bufferSize];
        GLsizei length = 0;
        glGetShaderInfoLog(m_handle, bufferSize, &length, buffer);
        m_inError = true;
        m_error = std::string(buffer, length);
    }
}

Shader::~Shader() {
    if (m_handle > 0) {
        glDeleteShader(m_handle);
        m_handle = 0;
    }
}

GLint Shader::handle() const {
    return m_handle;
}

bool Shader::inError() const {
    return m_inError;
}

const std::string& Shader::error() const {
    return m_error;
}
