#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec2 TexCoord2;

uniform sampler2D texture2;

void main()
{
	FragColor = texture(texture2, TexCoord) *vec4(ourColor, 1.0f);
}