#version 420

in vec2 texCoord;
out vec4 fragColor;

// texture sampler
uniform sampler2D tex;

void main(void)
{
    fragColor = texture(tex, texCoord);
}
