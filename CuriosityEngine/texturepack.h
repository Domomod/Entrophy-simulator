#ifndef TEXTUREPACK_H
#define TEXTUREPACK_H

#include "texture.h"
#include "simpleTexture.h"

#include <iostream>

class TexturePack
{
    public:
        TexturePack(Texture *backgroundTexture, Texture *rTexture, Texture *gTexture, Texture *bTexture, SimpleTexture *blendMap)
        {
        m_backgroundTexture = backgroundTexture;
        m_rTexture = rTexture;
        m_gTexture = gTexture;
        m_bTexture = bTexture;
        m_blendMap = blendMap;
        }

        void Bind();

        ~TexturePack()
        {
        }
    protected:
    private:
        Texture *m_backgroundTexture;
        Texture *m_rTexture;
        Texture *m_gTexture;
        Texture *m_bTexture;
        SimpleTexture *m_blendMap;

};

#endif // TEXTUREPACK_H
