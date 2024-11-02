#include "MeshBuilder.hpp"

namespace Pz::Mesh
{

void MeshBuilder::addVertex(const Vertex &vertex)
{
    // Check if the vertex is already in the list
    // If it is, add the index of the existing vertex to the indices array
    // If it is not, add the vertex to the vertices array and add the index of the new vertex to the indices array

    auto it = std::find(m_vertices.begin(), m_vertices.end(), vertex);

    if (it != m_vertices.end())
    {
        m_indices.push_back(it - m_vertices.begin());
    }
    else
    {
        m_vertices.push_back(vertex);
        m_indices.push_back(m_vertices.size() - 1);
    }
}

void MeshBuilder::addLine(glm::vec2 start, glm::vec2 end, glm::vec3 color)
{
    // Add the start and end vertices to the vertices array
    // Add the indices of the start and end vertices to the indices array

    addVertex({{start.x, start.y, 0.0f}, color});
    addVertex({{end.x, end.y, 0.0f}, color});
}

} // namespace Pz::Mesh
