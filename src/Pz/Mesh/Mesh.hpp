#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

namespace Pz::Mesh
{

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;

    bool operator==(const Vertex &other) const
    {
        return position == other.position && color == other.color;
    }
};

class Mesh
{
  public:
    Mesh() = default;
    Mesh(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);
    ~Mesh();

    void create(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices);

    void draw() const;

  private:
    Mesh(const Mesh &) = delete;
    Mesh &operator=(const Mesh &) = delete;
    Mesh(Mesh &&) = delete;
    Mesh &operator=(Mesh &&) = delete;

  private:
    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;

    size_t m_indexCount = 0;
};

} // namespace Pz::Mesh
