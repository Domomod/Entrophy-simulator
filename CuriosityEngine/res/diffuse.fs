#version 430

uniform vec3 materialDiffuse;

vec3 diffuse(vec3 normal, vec3 lightDirection, vec3 lightColor, vec4 surfaceColor, float Att)
{
		float diff =  dot(-lightDirection, normal) * Att;
		diff = clamp(diff, 0.0, 1.0);
		vec3 diffuseComponent = vec3(surfaceColor.rgb * lightColor * diff);
		return diffuseComponent;
}