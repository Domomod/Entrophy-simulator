#ifndef TEXTURES_H
#define TEXTURES_H

#include "../texture.h"
#include "../simpleTexture.h"
#include "../texturepack.h"

namespace Textures
{
    static Texture red;
    static Texture blue;
	static Texture black;

    inline void Load()
    {
        Textures::red.LoadTexture("./res/textures/red.png");
        Textures::blue.LoadTexture("./res/textures/blue.png");
		Textures::black.LoadTexture("./res/textures/black.png");
    }
}
#endif // TEXTURES_H
