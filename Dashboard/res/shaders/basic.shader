#shader vertex
#version 410

layout(location = 0)in vec3 vp;
layout(location = 1)in vec2 vt;

uniform mat4 matrix;

out vec2 texture_coordinates;

void main()
{
	texture_coordinates = vt;
	gl_Position = matrix * vec4(vp, 1.0f);
}

#shader fragment
#version 410

in vec2 texture_coordinates;

uniform vec4 inputColor;
uniform sampler2D basic_texture;

out vec4 frag_color;

void main()
{
	vec4 texel = texture(basic_texture, texture_coordinates);
	frag_color = texel;
}