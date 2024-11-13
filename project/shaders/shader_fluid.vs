#version 410 core
layout (location = 0) in vec3 aPos;

out VS_OUT {
    vec3 FragPos;
} vs_out;

uniform mat4 view;
uniform mat4 projection;

void main()
{
    vs_out.FragPos = aPos;

    gl_Position = projection * view * vec4(aPos, 1.0f);
}
