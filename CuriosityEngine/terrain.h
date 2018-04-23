#ifndef TERRAIN_H
#define TERRAIN_H

#include "mesh.h"
#include "texturepack.h"

static const float TERRAIN_SIZE = 1600;
static const int VERTEX_COUNT = 128;

class Terrain
{
public:
    Terrain(int gridX, int gridZ, TexturePack &texture_pack, Material &material)
    {
        this->m_texture_pack = &texture_pack;
        this->m_x = gridX * TERRAIN_SIZE;
        this->m_z = gridZ * TERRAIN_SIZE;
        this->m_material = &material;
        generateTerrain();
    }
    virtual ~Terrain();

    inline float& GetX() { return m_x; }

    inline float& GetZ() { return m_z; }

    inline Mesh* GetModel() { return m_model; }

    inline TexturePack* GetTexture() { return m_texture_pack; }

    inline Material* GetMaterial() { return m_material; }

    float GetHeight(float x, float z);

protected:

private:
    void generateTerrain();

    float heights[VERTEX_COUNT+1][VERTEX_COUNT+1];
    float m_x;
    float m_z;
    Mesh *m_model;
    TexturePack *m_texture_pack;
    Material *m_material;
};

#endif // TERRAIN_H
