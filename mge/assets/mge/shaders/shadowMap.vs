#version 330 // for glsl version (12 is for older versions , say opengl 2.1)

in vec3 vertex;
in vec2 uv;
uniform mat4 light_MVP;

out vec2 TexCoords;

void main( void )
{
	gl_Position = vec4(vertex,1);
	TexCoords = uv;
}
