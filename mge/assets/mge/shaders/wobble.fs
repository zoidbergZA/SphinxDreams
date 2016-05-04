//DIFFUSE COLOR FRAGMENT SHADER

#version 330 // for glsl version (12 is for older versions , say opengl 2.1

uniform vec3 diffuseColor;
uniform vec2 _time;

out vec4 fragment_color;
float rand(vec2 n)
{
  return 0.5 + 0.5 * fract(sin(dot(n.xy, vec2(12.9898, 78.233)))* 43758.5453);
}

void main( void ) {
	fragment_color = vec4 (diffuseColor, 1);
    //fragment_color = vec4(rand(_time), 1.0, rand(_time), 1.0);
}
