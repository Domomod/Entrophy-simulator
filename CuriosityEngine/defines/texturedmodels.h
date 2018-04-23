#ifndef TEXTUREDMODELS_H
#define TEXTUREDMODELS_H

#include "materials.h"
#include "textures.h"
#include "meshes.h"
namespace TexturedModels
{
    static TexturedModel atom_model;
	static TexturedModel quad_model;
	static TexturedModel quad_black_model;
    inline void Load()
    {
        TexturedModels::atom_model.LoadTexturedModel(&Meshes::atom, &Textures::red, &simple);
        TexturedModels::quad_model.LoadTexturedModel(&Meshes::quad, &Textures::blue, &simple);
		TexturedModels::quad_black_model.LoadTexturedModel(&Meshes::quad, &Textures::black, &simple);
    }
}

#endif // TEXTUREDMODELS_H
