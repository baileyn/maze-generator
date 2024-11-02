#pragma once

#include <filesystem>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <memory>

namespace Pz::Shader
{

class Program
{
  public:
    Program();

    void attachShader(const std::filesystem::path &path, GLenum type);
    void link();

    void use()
    {
        glUseProgram(m_id);
    }

    void setUniform(const std::string &name, int value)
    {
        glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
    }

    void setUniform(const std::string &name, const glm::mat4 &value)
    {
        glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, GL_FALSE, &value[0][0]);
    }

  private:
    Program(const Program &) = delete;
    Program(Program &&) = delete;
    Program &operator=(const Program &) = delete;
    Program &operator=(Program &&) = delete;

  private:
    GLuint m_id;
};

using ProgramPtr = std::shared_ptr<Program>;

} // namespace Pz::Shader
