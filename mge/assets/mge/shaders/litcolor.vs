//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;
uniform mat4 light_MVP;
uniform vec3 lightPos;

in vec3 vertex;
in vec3 normal;
in vec2 uv;

out vec3 wNormal;
out vec3 worldPosition;
out vec2 texCoord; //make sure the texture coord is interpolated
out vec4 lightVertexPos;

void main( void )
{
	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * vec4(vertex,1);
    worldPosition = vec3(modelMatrix * vec4(vertex,1));
    wNormal = normalize(vec3 (modelMatrix * vec4 (normal,0)));
    texCoord = uv;
    //lightVertexPos = vec3(light_MVP * vec4(worldPosition,1));
    lightVertexPos = light_MVP * vec4(worldPosition,1); //or should be vertex here instead of worldPosition?
}
