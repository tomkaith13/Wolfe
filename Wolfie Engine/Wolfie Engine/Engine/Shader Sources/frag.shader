#version 330 core
in vec4 color_out;
in vec2 uv_coords;
out vec4 color;
uniform sampler2D ourTexture;
void main()
{
//color = color_out;
//color = texture(ourTexture, uv_coords) * color_out;
color = texture(ourTexture, uv_coords);
}