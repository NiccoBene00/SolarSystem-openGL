#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    // colore base per debug
    vec3 color = vec3(0.4, 0.7, 1.0);

    // luce semplice
    vec3 lightPos = vec3(0.0, 0.0, 2.0);
    vec3 lightColor = vec3(1.0);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    vec3 result = diff * lightColor * color;

    FragColor = vec4(result, 1.0);
}