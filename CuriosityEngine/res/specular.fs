#version 430

varying vec3 normal0;
varying vec3 position0;

uniform vec3 cameraPos;

vec3 specular(vec3 normal, vec3 lightDirection, vec3 lightSpecular,vec3 lightColor, float materialShininess)
{
	lightDirection = normalize(lightDirection);

	vec3 reflectionVector = reflect(lightDirection, normalize(normal));
	vec3 surfaceToCamera = normalize(cameraPos - position0);
	float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
	vec3 specularComponent = lightSpecular *
							pow(max(dot(reflectionVector,surfaceToCamera),0.0f),0.3f*materialShininess);
	specularComponent = clamp(specularComponent, 0.0f, 1.0f);
	return specularComponent;
}