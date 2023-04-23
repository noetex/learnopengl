#version 330 core

in vec3 PixelColor;
out vec4 FragmentColor;

in vec2 TexCoords;

uniform sampler2D Texture;

void main()
{
	FragmentColor = texture(Texture, TexCoords);
}