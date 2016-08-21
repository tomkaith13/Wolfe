#version 330 core

in vec4 color_out;
out vec4 color;

void main()
{
    color = color_out;
}