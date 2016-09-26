#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color_in;
layout (location = 2) in vec2 uv;
layout (location = 3) in float tid;
uniform mat4 mvp;
out vec4 color_out;
out vec2 uv_coords;
out float frag_tid;
void main()
{
gl_Position =  mvp * position;
color_out = color_in;
uv_coords = vec2(uv.x, 1.0f - uv.y);
frag_tid = tid;
}
