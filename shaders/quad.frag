#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D scene;

void main()
{
    vec3 color = texture(scene, TexCoords).rgb;

    // tone mapping base
    color = color / (color + vec3(1.0));

    FragColor = vec4(color, 1.0);
}