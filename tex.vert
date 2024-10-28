#version 440 core

layout(location = 0) in vec2 aPos;      // Vertex position
layout(location = 1) in vec2 aTexCoord; // Texture coordinate

out vec2 texCoord; // Pass texture coordinate to fragment shader

uniform mat4 projection; // Projection matrix

void main()
{
    gl_Position = projection * vec4(aPos, 1.0, 1.0); // Set the vertex position in clip space
    texCoord = aTexCoord;               // Pass the texture coordinate to the fragment shader
}