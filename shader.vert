#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color;
layout (location = 2) in vec2 TexCoord;

out vec3 PixelColor;
out vec2 TexCoords;

uniform mat4 Transform;

void main()
{
	gl_Position = Transform * vec4(Position, 1.0f);
	PixelColor = Color;
	TexCoords = TexCoord;
}