#version 330 core
layout (location = 0) in vec3 position; //d
layout (location = 1) in vec3 normal; //d
layout (location = 2) in vec2 texCoords; //d

out vec2 TexCoords;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 projection; //d
uniform mat4 view; //d
uniform mat4 model; //d
uniform mat4 lightSpaceMatrix; //d

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    vs_out.FragPos = vec3(model * vec4(position, 1.0));
    vs_out.Normal = transpose(inverse(mat3(model))) * normal;
    vs_out.TexCoords = texCoords;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(vs_out.FragPos, 1.0);
}
