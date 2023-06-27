#version 420 core

out vec4 fragColor;

in vec2 texCoord;

// texture sampler
uniform sampler2D tex;

void main()
{
    fragColor = texture(tex, texCoord);
}