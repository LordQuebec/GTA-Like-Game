#version 460 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec4 vertexColor;

uniform mat4 ModelMatrix;

out vec4 color;

void main()
{
	vec4 pos = vec4(vertexPosition, 1);
	gl_Position = pos * ModelMatrix;
	color = vertexColor;
}