#version 420

uniform mat4 viewingMatrix;
uniform mat4 modelingMatrix;
uniform mat4 projectionMatrix;

layout(location=0) in vec3 inVertex;
layout(location=1) in vec3 inNormal;

out vec2 texCoord;

void main(void)
{
    texCoord = inVertex.xz * 1; // multiply to increase resolution
    gl_Position = projectionMatrix * viewingMatrix * modelingMatrix * vec4(inVertex, 1);
}