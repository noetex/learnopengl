#version 330 core

in vec3 PixelColor;
out vec4 FragmentColor;

void main()
{
	FragmentColor = vec4(PixelColor, 1.0f);
}