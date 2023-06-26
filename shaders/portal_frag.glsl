#version 420 core

// All of the following variables could be defined in the OpenGL
// program and passed to this shader as uniform variables. This
// would be necessary if their values could change during runtim.
// However, we will not change them and therefore we define them
// here for simplicity.

out vec4 fragColor;

void main(void)
{
	fragColor = vec4(0.69, 0.17, 0.5, 1);
}
