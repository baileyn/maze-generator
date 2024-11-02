#version 400 core

layout(location = 0) in vec3 position; // Vertex position attribute
layout(location = 1) in vec3 color; // Vertex color attribute

out vec3 passColor; // Output color to the fragment shader

void main()
{
    gl_Position = vec4(position, 1.0); // Set the position of the vertex
    passColor = color; // Pass the color to the fragment shader
}
