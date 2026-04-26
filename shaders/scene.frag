#version 330 core
layout (location = 0) out vec4 FragColor;
layout (location = 1) out vec4 BrightColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform sampler2D diffuseMap;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform int isEmissive;

void main()
{
    vec3 color = texture(diffuseMap, TexCoords).rgb;

    if (isEmissive == 1)
    {
        vec3 result = color * 10.0;

        FragColor = vec4(result, 1.0);
        BrightColor = vec4(result, 1.0); 

        return;
    }

    // ambient
    vec3 ambient = 0.1 * color;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * color;

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = vec3(0.3) * spec;

    vec3 result = ambient + diffuse + specular;

    FragColor = vec4(result, 1.0);

    //BRIGHT PASS
    float brightness = dot(result, vec3(0.2126, 0.7152, 0.0722));

    if (brightness > 1.0)
        BrightColor = vec4(result, 1.0);
    else
        BrightColor = vec4(0.0, 0.0, 0.0, 1.0);
}