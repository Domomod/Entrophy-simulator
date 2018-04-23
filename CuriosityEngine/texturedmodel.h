#ifndef TEXTUREDMODEL_H
#define TEXTUREDMODEL_H

#include "mesh.h"
#include "texture.h"
#include "material.h"

class TexturedModel
{
    public:
        TexturedModel()
        {
        }
        TexturedModel(Mesh *rawModel, Texture *texture, Material *material)
        {
            this->m_rawModel = rawModel;
            this->m_texture = texture;
            this->m_material = material;
        }
        virtual ~TexturedModel();

        void LoadTexturedModel(Mesh *rawModel, Texture *texture, Material *material)
        {
            this->m_rawModel = rawModel;
            this->m_texture = texture;
            this->m_material = material;
        }
        Mesh *GetRawModel() { return m_rawModel; }
        void SetrawModel(Mesh rawModel) { *m_rawModel = rawModel; }
        Texture *GetTexture() { return m_texture; }
        void Settexture(Texture texture) { *m_texture = texture; }
        Material *GetMaterial() { return m_material; }
        void Setmaterial(Material material) { *m_material = material; }

    protected:

    private:
        Mesh *m_rawModel;;
        Texture *m_texture;
        Material *m_material;
};

#endif // TEXTUREDMODEL_H
