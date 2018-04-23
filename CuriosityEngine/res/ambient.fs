#version 430

uniform vec3 materialAmbient;

vec3 ambient(float AmbientCoefficient,vec3 lightColor, vec4 surfaceColor, float Att)
{
	vec3 ambientComponent = AmbientCoefficient * surfaceColor.rgb * Att;
	return ambientComponent;
}