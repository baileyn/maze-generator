#version 400 core

layout(location = 0) in vec2 aPos; // Vertex position attribute
layout(location = 1) in vec3 aColor; // Vertex color attribute

out vec3 vertexColor; // Output color to the fragment shader

// View matrix
uniform mat4 view;

void main()
{
    gl_Position = view * vec4(aPos, 0.0, 1.0); // Set the position of the vertex
    vertexColor = aColor; // Pass the color to the fragment shader
}

// vim: set ft=glsl
