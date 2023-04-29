#version 330 core

out vec4 FragmentColor;

in vec2 TexCoords;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main()
{
	vec4 Color1 = texture(Texture1, TexCoords);
	vec4 Color2 = texture(Texture2, TexCoords);
	FragmentColor = mix(Color1, Color2, 0.2);
}