#version 330 core
in vec4 color_out;
in vec2 uv_coords;
in float frag_tid;
out vec4 color;
uniform sampler2D TextureSamplerArr[16];
void main()
{
//color = color_out;
//color = texture(TextureSamplerArr, uv_coords) * color_out;

if (frag_tid >= 0.0)
{
int tid = int (frag_tid);
color = texture(TextureSamplerArr[tid], uv_coords);
} else {
//color = color_out;
color = vec4(0.0, 1.0, 0.0, 0.0);

}

}
