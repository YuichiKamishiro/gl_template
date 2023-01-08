#version 330 core

out vec4 frag_color;
in vec3 colors;

void main()
{
    frag_color = vec4(colors, 1);
} 
