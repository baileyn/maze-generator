#include "ShaderProgram.hpp"

#include <fstream>
#include <vector>

namespace
{

std::string readFile(const fs::path &path)
{
    if (!fs::exists(path))
    {
        throw std::runtime_error("File does not exist: " + path.string());
    }

    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open file: " + path.string());
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

} // namespace

ShaderProgram::ShaderProgram()
{
    m_id = glCreateProgram();
}

void ShaderProgram::addShader(const fs::path &path, GLenum type)
{
    std::string source = readFile(path);
    GLuint shader = glCreateShader(type);

    const char *sourcePtr = source.c_str();
    glShaderSource(shader, 1, &sourcePtr, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

        throw std::runtime_error("Failed to compile shader: " + path.string() + "\n" + infoLog);
    }

    glAttachShader(m_id, shader);
    glDeleteShader(shader);
}

void ShaderProgram::link()
{
    glLinkProgram(m_id);

    GLint success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);

    if (!success)
    {
        GLchar infoLog[512];
        glGetProgramInfoLog(m_id, sizeof(infoLog), nullptr, infoLog);

        throw std::runtime_error("Failed to link shader program\n" + std::string(infoLog));
    }
}