#version 330

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 position0;
varying mat3 tbnMatrix;

varying vec3 tan;
varying vec3 biTan;
varying vec3 norm;
varying float check;

uniform sampler2D textureMap;
uniform sampler2D normalMap;
uniform sampler2D dispMap;

uniform float dispMapScale;
uniform float dispMapBias;


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

vec3 diffuse(vec3 normal, vec3 lightDirection, int i, vec4 surfaceColor, float ConstAtt, float LinearAtt, float QuadraticAtt);
vec3 specularLightning(vec3 normal, vec3 lightDirection, vec3 lightColor);
vec3 ambient(vec4 surfaceColor);

vec2 ParallaxMapping(vec3 viewDir)
{
    // number of depth layers
	const float minLayers = 8;
	const float maxLayers = 8;
	float numLayers = mix(maxLayers, minLayers, abs(dot(normal0, viewDir)));  
    // calculate the size of each layer
    float layerDepth = 1.0 / numLayers;
    // depth of current layer
    float currentLayerDepth = 0.0;
    // the amount to shift the texture coordinates per layer (from vector P)
    vec2 P = viewDir.xy * dispMapScale; 
    vec2 deltaTexCoords = P / numLayers;
	// get initial values
	vec2  currentTexCoords     = texCoord0;
	float currentDepthMapValue = texture(dispMap, currentTexCoords).r;
	  
	while(currentLayerDepth < currentDepthMapValue)
	{
		// shift texture coordinates along direction of P
		currentTexCoords -= vec2(-deltaTexCoords.x, deltaTexCoords.y);
		// get depthmap value at current texture coordinates
		currentDepthMapValue = texture(dispMap, currentTexCoords).r;  
		// get depth of next layer
		currentLayerDepth += layerDepth;  
	}

	// get texture coordinates before collision (reverse operations)
	vec2 prevTexCoords = currentTexCoords + vec2(-deltaTexCoords.x, deltaTexCoords.y);

	// get depth after and before collision for linear interpolation
	float afterDepth  = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(dispMap, prevTexCoords).r - currentLayerDepth + layerDepth;
	 
	// interpolation of texture coordinates
	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

	return finalTexCoords;  
}

void main()
{
	vec3 surfaceToCamera = normalize(cameraPos - position0);
	vec2 texCoords = ParallaxMapping(surfaceToCamera * tbnMatrix);

	vec3 normal = tbnMatrix * ((255.0/128.0 * texture2D(normalMap, texCoords).xyz) - 1);

	 vec3 Color = vec3(0.0f, 0.0f, 0.0f);
	
	vec4 surfaceColor = texture2D(textureMap, texCoords);
	//surfaceColor = vec4(0,1,0.5,1);
	
		for(int i=0;i<3;i++)
		{
		//Ambient
		
		Color += ambient( surfaceColor);
		
		//DIffuse
		vec3 lightDirection = position0 - lightPosition[i];

		Color += diffuse(normal, lightDirection, i, surfaceColor,  lightConstAtt[i], lightLinearAtt[i], lightQuadraticAtt[i]);

		Color += specularLightning(normal, lightDirection, lightColor[i]);
		
	}

//Color = abs(surfaceToCamera * tbnMatrix);
	
gl_FragColor =  vec4(Color,  1);
}