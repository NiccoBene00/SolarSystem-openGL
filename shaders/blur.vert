#version 330 core
layout (location = 0) in vec2 aPos; //2D vertex position
layout (location = 1) in vec2 aTexCoords; //UV coordinates

out vec2 TexCoords;

void main()
{
    TexCoords = aTexCoords; //pass UV coordinates to fragment shader
    gl_Position = vec4(aPos, 0.0, 1.0);
}