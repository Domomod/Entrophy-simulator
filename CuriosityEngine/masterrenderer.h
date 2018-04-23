#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include <vector>

#include "light.h"
#include "entity.h"
#include "shader.h"
#include "renderer.h"
#include "terrain.h"
#include "TerrainShader.h"
#include "terrainrenderer.h"


class MasterRenderer
{
public:
//    private static final float FOV = 70;
//    private static final float NEAR_PLANE = 0.1f;
//    private static final float FAR_PLANE = 1000;
//    private Matrix4f projectionMatrix;
    MasterRenderer(Shader *shaderPointer, TerrainShader *terrainShaderPointer);

    void Render(std::vector<Entity> entities, std::vector<Terrain> terrains, std::vector<Light> lights, Camera camera);
    void Prepare();

    Shader *shader;
    EntityRenderer renderer;

    TerrainRenderer terrainRenderer;
    TerrainShader *terrainShader ;
//
//    std::vector<Entity> *entities;
//    std::vector<Terrain> *terrains;
};

#endif // MASTERRENDERER_H
