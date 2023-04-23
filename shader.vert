#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;

out vec3 PixelColor;
out vec2 TexCoords;

void main()
{
	gl_Position = vec4(Position, 1.0f);
	PixelColor = Color;
	TexCoords = TexCoord;
}