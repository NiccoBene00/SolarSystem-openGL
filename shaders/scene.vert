#version 330 core
layout (location = 0) in vec3 aPos; 
layout (location = 1) in vec3 aNormal; 
layout (location = 2) in vec2 aTexCoords; //UV

//output to the fragment shader
out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoords;

uniform mat4 model; //model matrix
uniform mat4 view; //amera matrix
uniform mat4 projection; //perspective matrix

void main()
{   
    //bring the vertex from local space to world space
    //it used for the computation of the lights
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    Normal = mat3(transpose(inverse(model))) * aNormal;

    TexCoords = aTexCoords;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}