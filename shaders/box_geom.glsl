#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 10) out;

uniform mat4 projectionMatrix;
uniform mat4 viewingMatrix;
uniform mat4 modelingMatrix;

out vec2 texCoord;

float portal1_pos = -2.0; //TODO: check x coords and split if they pass through portal (it will be hardcoded for current scene)
float portal2_pos = 2.0;

void emit(vec4 v1, vec4 v2, vec4 v3, vec4 v4, float texStart, float texEnd)
{
    gl_Position = projectionMatrix * viewingMatrix * v1;
    texCoord = vec2(texEnd, 1.0);
    EmitVertex();

    gl_Position = projectionMatrix * viewingMatrix * v2;
    texCoord = vec2(texEnd, 0.0);
    EmitVertex();

    gl_Position = projectionMatrix * viewingMatrix * v3;
    texCoord = vec2(texStart, 0.0);
    EmitVertex();

    gl_Position = projectionMatrix * viewingMatrix * v4;
    texCoord = vec2(texStart, 1.0);
    EmitVertex();

    gl_Position = projectionMatrix * viewingMatrix * v1;
    texCoord = vec2(texEnd, 1.0);
    EmitVertex();

    EndPrimitive();
}

void main()
{
    if (gl_in[0].gl_Position.x != 0.0)
    {
        vec4 v1 = modelingMatrix * vec4(gl_in[0].gl_Position.x, 1.5f, 0.5f, 1.0f);
        vec4 v2 = modelingMatrix * vec4(gl_in[0].gl_Position.x, 1.5f, -0.5f, 1.0f);
        vec4 v3 = modelingMatrix * vec4(gl_in[0].gl_Position.x, 0.5f, -0.5f, 1.0f);
        vec4 v4 = modelingMatrix * vec4(gl_in[0].gl_Position.x, 0.5f, 0.5f, 1.0f);
        
        if (v1.x > 2.0) 
        {
            v1.x -= 4.0;
            v2.x -= 4.0;
            v3.x -= 4.0;
            v4.x -= 4.0;
        }
        else if (v1.x < -2.0) 
        {
            v1.x += 4.0;
            v2.x += 4.0;
            v3.x += 4.0;
            v4.x += 4.0;
        }

        emit(v1, v2, v3, v4, 0.0, 1.0);
    }

    else if (gl_in[0].gl_Position.z != 0.0)
    {
        vec4 v1 = modelingMatrix * vec4(0.5f, 1.5f, gl_in[0].gl_Position.z, 1.0f);
        vec4 v2 = modelingMatrix * vec4(0.5f, 0.5f, gl_in[0].gl_Position.z, 1.0f);
        vec4 v3 = modelingMatrix * vec4(-0.5f, 0.5f, gl_in[0].gl_Position.z, 1.0f);
        vec4 v4 = modelingMatrix * vec4(-0.5f, 1.5f, gl_in[0].gl_Position.z, 1.0f);
        
        if (v1.x > 2.0)
        {
            v1.x -= 4.0;
            v2.x -= 4.0;

            vec4 v5 = vec4(-2.0f, v2.yz, 1.0f);
            vec4 v6 = vec4(-2.0f, v1.yz, 1.0f);

            emit(v1, v2, v5, v6, -v1.x - 1.0, 1.0);

            vec4 v7 = vec4(2.0f, v1.yz, 1.0f);
            vec4 v8 = vec4(2.0f, v2.yz, 1.0f);

            emit(v7, v8, v3, v4, 0.0, -v1.x - 1.0);
        }
        else if (v3.x < -2.0)
        {
            v3.x += 4.0;
            v4.x += 4.0;

            vec4 v5 = vec4(-2.0f, v2.yz, 1.0f);
            vec4 v6 = vec4(-2.0f, v1.yz, 1.0f);

            emit(v1, v2, v5, v6, 2.0 - v3.x, 1.0);

            vec4 v7 = vec4(2.0f, v1.yz, 1.0f);
            vec4 v8 = vec4(2.0f, v2.yz, 1.0f);

            emit(v7, v8, v3, v4, 0.0, 2.0 - v3.x);
        }
        else
        {
            emit(v1, v2, v3, v4, 0.0, 1.0);
        }
    }

    else if (gl_in[0].gl_Position.y != 0.0)
    {
        vec4 v1 =  modelingMatrix * vec4(0.5f, gl_in[0].gl_Position.y, 0.5f, 1.0f);
        vec4 v2 =  modelingMatrix * vec4(0.5f, gl_in[0].gl_Position.y, -0.5f, 1.0f);
        vec4 v3 =  modelingMatrix * vec4(-0.5f, gl_in[0].gl_Position.y, -0.5f, 1.0f);
        vec4 v4 =  modelingMatrix * vec4(-0.5f, gl_in[0].gl_Position.y, 0.5f, 1.0f);

        if (v1.x > 2.0)
        {
            v1.x -= 4.0;
            v2.x -= 4.0;

            vec4 v5 = vec4(-2.0f, v2.yz, 1.0f);
            vec4 v6 = vec4(-2.0f, v1.yz, 1.0f);

            emit(v1, v2, v5, v6, -v1.x - 1.0, 1.0);

            vec4 v7 = vec4(2.0f, v1.yz, 1.0f);
            vec4 v8 = vec4(2.0f, v2.yz, 1.0f);

            emit(v7, v8, v3, v4, 0.0, -v1.x - 1.0);
        }
        else if (v3.x < -2.0)
        {
            v3.x += 4.0;
            v4.x += 4.0;

            vec4 v5 = vec4(-2.0f, v2.yz, 1.0f);
            vec4 v6 = vec4(-2.0f, v1.yz, 1.0f);

            emit(v1, v2, v5, v6, 2.0 - v3.x, 1.0);

            vec4 v7 = vec4(2.0f, v1.yz, 1.0f);
            vec4 v8 = vec4(2.0f, v2.yz, 1.0f);

            emit(v7, v8, v3, v4, 0.0, 2.0 - v3.x);
        }
        else
        {
            emit(v1, v2, v3, v4, 0.0, 1.0);
        }
    }
}
