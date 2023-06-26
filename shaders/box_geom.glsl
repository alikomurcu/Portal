#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

uniform mat4 projectionMatrix;
uniform mat4 viewingMatrix;
uniform mat4 modelingMatrix;

float portal1_pos = -2.0; //TODO: check x coords and split if they pass through portal (it will be hardcoded for current scene)
float portal2_pos = 2.0;

void main()
{
    if (gl_in[0].gl_Position.x != 0.0)
    {
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(gl_in[0].gl_Position.x, 1.5f, 0.5f, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(gl_in[0].gl_Position.x, 1.5f, -0.5f, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(gl_in[0].gl_Position.x, 0.5f, -0.5f, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(gl_in[0].gl_Position.x, 0.5f, 0.5f, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(gl_in[0].gl_Position.x, 1.5f, 0.5f, 1.0f);
        EmitVertex();
    }

    else if (gl_in[0].gl_Position.z != 0.0)
    {
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(0.5f, 1.5f, gl_in[0].gl_Position.z, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(0.5f, 0.5f, gl_in[0].gl_Position.z, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(-0.5f, 0.5f, gl_in[0].gl_Position.z, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(-0.5f, 1.5f, gl_in[0].gl_Position.z, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(0.5f, 1.5f, gl_in[0].gl_Position.z, 1.0f);
        EmitVertex();
    }

    else if (gl_in[0].gl_Position.y != 0.0)
    {
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(0.5f, gl_in[0].gl_Position.y, 0.5f, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(0.5f, gl_in[0].gl_Position.y, -0.5f, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(-0.5f, gl_in[0].gl_Position.y, -0.5f, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(-0.5f, gl_in[0].gl_Position.y, 0.5f, 1.0f);
        EmitVertex();
        gl_Position =  projectionMatrix * viewingMatrix * modelingMatrix * vec4(0.5f, gl_in[0].gl_Position.y, 0.5f, 1.0f);
        EmitVertex();
    }

    EndPrimitive();
}
