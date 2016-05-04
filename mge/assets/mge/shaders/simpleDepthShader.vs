#version 330 core
//layout (location = 0) in vec3 position;

uniform mat4 lightSpaceMatrix;
uniform mat4 modelMatrix;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

void main()
{
    gl_Position = lightSpaceMatrix * modelMatrix * vec4(vertex, 1.0f);
}
