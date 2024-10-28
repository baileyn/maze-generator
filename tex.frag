#version 440 core  // Specify the GLSL version

out vec4 fragColor;  // Output color of the fragment
in vec2 texCoord;  // Input texture coordinate from the vertex shader

uniform sampler2D textureSampler;  // The texture sampler

void main()
{
    fragColor = texture(textureSampler, texCoord);  // Sample the texture using the texture coordinate
}
