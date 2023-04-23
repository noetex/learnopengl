#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;

out vec3 PixelColor;
uniform float Offset;

void main()
{
	gl_Position = vec4(Position.x + Offset, Position.yz, 1.0f);
	PixelColor = Color;
}