#version 460 core

in vec4 color;
out vec4 vertexColor;

void main()
{
	vertexColor = color;
}