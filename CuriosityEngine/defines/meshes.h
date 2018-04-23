#ifndef MESHES_H
#define MESHES_H

namespace Meshes
{
    static Mesh atom;
    static Mesh quad;

    inline void Load()
    {
        Meshes::atom.LoadMesh("./res/OBJ/sphere2.obj");
        Meshes::quad.LoadMesh("./res/OBJ/quad.obj");
    }
}

#endif // MESHES_H
