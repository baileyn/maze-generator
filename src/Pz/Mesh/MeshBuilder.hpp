#pragma once

#include "../Core/Logging.hpp"
#include "Mesh.hpp"

#include <memory>
#include <vector>

namespace Pz::Mesh
{

class MeshBuilder
{
  public:
    MeshBuilder() = default;
    ~MeshBuilder() = default;

    void addVertex(const Vertex &vertex);
    void addLine(glm::vec2 start, glm::vec2 end, glm::vec3 color = {0.0, 0.0, 0.0});

    std::shared_ptr<Mesh> build() const
    {
        // Trace vertices
        for (const auto &vertex : m_vertices)
        {
            PZ_CORE_DEBUG("Vertex: {0}, {1}, {2}", vertex.position.x, vertex.position.y, vertex.position.z);
        }

        // Trace indices
        for (const auto &index : m_indices)
        {
            PZ_CORE_DEBUG("Index: {0}", index);
        }

        return std::make_shared<Mesh>(m_vertices, m_indices);
    }

    void reset()
    {
        m_vertices.clear();
        m_indices.clear();
    }

  private:
    std::vector<Vertex> m_vertices{};
    std::vector<unsigned int> m_indices{};
};

} // namespace Pz::Mesh
