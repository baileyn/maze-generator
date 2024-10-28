#version 400 core

in vec3 vertexColor; // Input color from the vertex shader

out vec4 FragColor; // Output color

void main()
{
    FragColor = vec4(vertexColor, 1.0); // Set the fragment color
}

// vim: set ft=glsl
