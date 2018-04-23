#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;
attribute vec3 tangent;

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 position0;
varying mat3 tbnMatrix;

uniform mat4 transform;
uniform mat4 model;

void main()
{
	position0 = (model * vec4( position, 1.0)).xyz; //tu jest chyba błąd
	gl_Position = transform  * vec4(position,  1.0);
	texCoord0 = texCoord;
	normal0 = (model * vec4(normal, 0.0)).xyz;
	
	
	
	vec3 n = normalize((model * vec4(normal, 0.0)).xyz);
	vec3 t = normalize((model * vec4(tangent, 0.0)).xyz);
	
	//t = normalize(t - dot(t, n) * n);
	
	vec3 b = cross(t, n);
	
	tbnMatrix = mat3(t, b, n);
}