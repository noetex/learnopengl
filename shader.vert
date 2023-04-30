#version 330 core
layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;

out vec2 TexCoords;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Perspective;

void main()
{
	gl_Position = Perspective * View * Model * vec4(Position, 1.0f);
	TexCoords = TexCoord;
}