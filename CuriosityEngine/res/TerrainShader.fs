#version 430

struct LightSource
{
/*
This structure handles all types of Light Sources.
Type:[int]0- directional, 1- point light, 2- spot light(not implemented yet)
Position:[vec3] position of light source, only matters in point and spot 
Attenuation:[vec3] [ConstantAttenuation, LinearAttenuation,QuadratiocAttenuation] attenuation descibes the gradual loss of flux in a medium:
					const- 
					linear- 
					quadratis- 
Direction:[vec3] 	for directional light it's the direction of rays of light
					for spot light it's the direction of the cone of light
Color:[vec3] color of the light in rgb
*/
        int Type;
        vec3 Position;
        vec3 Attenuation;
        vec3 Direction;
        vec3 Color;
		float AmbientCoefficient;
};
const int MAX_LIGHTS = 8;
uniform int NUM_LIGHTS = 3;
uniform LightSource lightSources[MAX_LIGHTS];

struct Material
{
/*
This structure descibes currently lit material. 
Emmision:[vec3]	the color of light object is emmiting
Ambient:[vec3] affects the outcome color of ambient lightning
Diffuse:[vec3] affects the outcome color of diffuse lightning
Specular:[vec3] affects the outcome of specular lightning
Shininess;[float] scale 0.0f to 1.0f how bright is the object shining
DispMapScale:[float]
DispMapBias:[float]
*/
	vec3 Emmision;
	vec3 Ambient;
	vec3 Diffuse;
	vec3 Specular;
	float Shininess;
	float DispMapScale;
	float DispMapBias;
};
uniform Material material;

in vec2 texCoord0;
in vec3 normal0;
in vec3 position0;
in mat3 tbnMatrix;
in float visibility;

in vec3 tan;
in vec3 biTan;
in vec3 norm;
in float check;

uniform sampler2D backgroundTexture;
uniform sampler2D normalMap;
uniform sampler2D dispMap;

uniform sampler2D rTexture;
uniform sampler2D rNormalMap;
uniform sampler2D rDispMap;

uniform sampler2D gTexture;
uniform sampler2D gNormalMap;
uniform sampler2D gDispMap;

uniform sampler2D bTexture;
uniform sampler2D bNormalMap;
uniform sampler2D bDispMap;

uniform sampler2D blendMap;

uniform mat4 transform;
uniform mat4 model;
uniform vec3 cameraPos;

uniform vec3 lightPosition[3];
uniform vec3 lightColor[3];
uniform float lightConstAtt[3];
uniform float lightLinearAtt[3];
uniform float lightQuadraticAtt[3];

uniform vec3 materialDiffuse;
uniform vec3 materialAmbient;

vec3 ambient(float AmbientCoefficient, vec3 lightColor, vec4 surfaceColor , float Att);
vec3 diffuse(vec3 normal, vec3 lightDirection, vec3 lightColor, vec4 surfaceColor, float Att);
vec3 specular(vec3 normal, vec3 lightDirection, vec3 lightSpecular,vec3 lightColor, float materialShininess);

vec3 ApplyLight(LightSource light, vec4 surfaceColor, vec3 surfaceToCamera, vec3 normal)
/*
Handles all calculations nedded to lit the object by any type of Light.
*/
{
	float dist = 1.0f;
	vec3 dir = vec3(0.0f, 0.0f, 0.0f);
	if(light.Type == 0)
	{	
		dir = light.Direction;
	}
	else
	{
		dir = position0 - light.Position;
		dist = length(dir);
		dir = normalize(dir);
	}
	float attenuation = min((1 / ( light.Attenuation[0] 
								+ (dist * light.Attenuation[1]) 
								+ (dist * dist * light.Attenuation[2]))), 1.0f);
	vec3 Color = vec3(0.0f, 0.0f, 0.0f);
	Color += ambient(light.AmbientCoefficient, light.Color, surfaceColor, attenuation);
	Color += diffuse(normal, dir, light.Color, surfaceColor, attenuation);
	Color += specular(normal, dir, material.Specular, light.Color, material.Shininess);
	
	return Color;
}

void main()
{
	vec4 blendMapColour = texture2D(blendMap, texCoord0);

	vec3 normalLightDirection = tbnMatrix * normalize(vec3(-1.0f ,1.0f, -1.0f));
	
	float backgroundTextureAmount = 1- (blendMapColour.r + blendMapColour.g + blendMapColour.b);
	
	vec3 surfaceToCamera = normalize(cameraPos - position0);
	vec2 backTiledCoords = texCoord0 * 80.0f;
	vec2 rTiledCoords = texCoord0 * 80.0f;
	vec2 gTiledCoords = texCoord0 * 80.0f;
	vec2 bTiledCoords = texCoord0 * 80.0f;

	vec4 backgroundTextureColor = texture2D(backgroundTexture, backTiledCoords) * backgroundTextureAmount;
	vec4 rTextureColor = texture2D(rTexture, rTiledCoords) * blendMapColour.r ;
	vec4 gTextureColor = texture2D(gTexture, gTiledCoords) * blendMapColour.g ;
	vec4 bTextureColor = texture2D(bTexture, bTiledCoords) * blendMapColour.b;
	
	vec4 surfaceColor = backgroundTextureColor + rTextureColor + gTextureColor + bTextureColor;
	vec3 normal = tbnMatrix * ((255.0f/128.0f * texture2D(normalMap, backTiledCoords).xyz) - 1.0f);
	
	vec3 Color = vec3(0.0f, 0.0f, 0.0f);
	for(int lightNum = 0; lightNum < NUM_LIGHTS; lightNum++)
	{
		Color += ApplyLight(lightSources[lightNum], surfaceColor, surfaceToCamera, normal);
	}
	Color = mix(vec3(0.16f, 0.32f, 0.6f), Color, visibility);
	
	vec3 gamma = vec3(1.0f/2.2f);
	vec3 ColorGamma = pow(Color,gamma);
	
	gl_FragColor = vec4( 0.5f*(Color + ColorGamma),  1.0f);
	}