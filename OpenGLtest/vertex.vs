#version 450 core
layout(location = 0) in vec4 position;
uniform float sherwintime;
out vec2 uv;
out vec3 backcolor;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
void main()
{
	gl_Position = projection * view * model * vec4(position.xyz, 1.0f);
	uv = position.xy;
	backcolor = ((position.xyz+1)/2);
}