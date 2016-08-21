#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color_in;

uniform mat4 mvp;
out vec4 color_out;

void main()
{
	gl_Position =  mvp * position;
	color_out = color_in;
}