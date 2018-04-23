#ifndef TERRAINRENDERER_H
#define TERRAINRENDERER_H

#include "terrain.h"
#include "TerrainShader.h"
#include "camera.h"

class TerrainRenderer
{
    public:
        void render(std::vector<Terrain> terrains, const Camera &camera, TerrainShader* shader);
        void PrepareTerrain(Terrain terrain, TerrainShader *shader);
        void UnbindTexturedModel();

    protected:
    private:
};

#endif // TERRAINRENDERER_H
