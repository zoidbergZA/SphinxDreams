//DIFFUSE COLOR VERTEX SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

in vec3 vertex;
in vec3 normal;
in vec2 uv;

uniform vec2 offset;
uniform	mat4 mvpMatrix;
uniform vec2 _time;

float rand(vec2 n)
{
  return 0.5 + 0.5 * fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}

void main( void )
{
    //stoned wobbling
	//gl_Position = mvpMatrix * vec4(vertex * vec3(cos(_time/2000.0f) + 2.0f, 1.0f), 1.f);

	//black rap effect
	//gl_Position = mvpMatrix * vec4(vertex * vec3(rand(_time), rand(_time), 1.0f), 1.f);

	//regular mesh
	gl_Position = mvpMatrix * vec4(vertex, 1.f);
}
