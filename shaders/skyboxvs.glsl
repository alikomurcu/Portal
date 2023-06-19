#version 420 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewingMatrix;

void main()
{
	TexCoords = aPos;
	vec4 pos = projectionMatrix * viewingMatrix * vec4(aPos, 1.0);
	gl_Position = pos.xyww;
}

