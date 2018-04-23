#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include <string>
#include <vector>
#include <Gl/glew.h>

#include "transform.h"
#include "camera.h"
#include "mesh.h"
#include "light.h"

class TerrainShader
{
public:
    TerrainShader() {}
    TerrainShader(const std::string& fileName);

    void Bind();
    void Detach();
    void Update(const Transform& transform, const Camera& camera);
    void UpdateMaterial(Material* material);
    void LoadLights(std::vector<Light> lights);

    TerrainShader(const TerrainShader& other);

    virtual ~TerrainShader();
protected:

private:
    static const unsigned int NUM_SHADERS = 5;
    void operator=(const TerrainShader& other) {}

    enum
    {
		TYPE_U,
		POSITION_U,
		ATTENUATION_U,
		DIRECTION_U,
		COLOR_U,
		AMBIENT_U,

		NUM_PARAMS_LIGHT
    };

	enum
	{
		MAT_EMMISION_U,
		MAT_AMBIENT_U,
		MAT_DIFFUSE_U,
		MAT_SPECULAR_U,
		MAT_SHININESS_U,
		MAT_DISP_SCALE_U,
		MAT_DISP_BIAS_U,

		NUM_PARAMS_MAT
	};

    enum
    {
        TRANSFORM_U,
        MODEL_U,
        CAMERA_POS_U,
        VIEW_MATRIX_U,

        NUM_UNIFORMS
    };

    GLuint m_program;
    GLuint m_shaders[NUM_SHADERS];
    GLuint m_uniforms[NUM_UNIFORMS];
	GLuint m_NumLights;
    GLuint m_LightSourceUniforms[NUM_PARAMS_LIGHT];
	GLuint m_MaterialUniforms[NUM_PARAMS_MAT];
};

#endif // TERRAINSHADER_H
