#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace fs = std::filesystem;

class ShaderProgram
{
  public:
    ShaderProgram();

    void addShader(const fs::path &path, GLenum type);
    void link();

    void use()
    {
        glUseProgram(m_id);
    }

  private:
    ShaderProgram(const ShaderProgram &) = delete;
    ShaderProgram(ShaderProgram &&) = delete;
    ShaderProgram &operator=(const ShaderProgram &) = delete;
    ShaderProgram &operator=(ShaderProgram &&) = delete;

  private:
    GLuint m_id;
};