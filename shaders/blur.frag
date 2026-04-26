#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D image; //texture to blur
uniform bool horizontal; //blur direction

void main()
{
    //gaussian weight
    float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

    vec2 tex_offset = 1.0 / textureSize(image, 0); //dimension of 1 pixel of the texture

    //take the central pixel
    vec3 result = texture(image, TexCoords).rgb * weight[0];


    //BLUR filter: for each pixel take the neighboors, do a weighted mean
    if(horizontal)
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoords + vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(tex_offset.x * i, 0.0)).rgb * weight[i];
        }
    }
    else
    {
        for(int i = 1; i < 5; ++i)
        {
            result += texture(image, TexCoords + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
            result += texture(image, TexCoords - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        }
    }

    FragColor = vec4(result, 1.0);
}