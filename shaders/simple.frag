#version 400 core

in vec3 passColor; // Input color from the vertex shader

out vec4 outColor; // Output color

void main()
{
    outColor = vec4(passColor, 1.0); // Set the fragment color
}
