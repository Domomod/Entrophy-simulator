#ifndef RENDERER_H
#define RENDERER_H

#include <vector>

#include "entity.h"
#include "shader.h"
#include "camera.h"

class EntityRenderer
{
    public:
        void render(std::vector<Entity> entities, Shader *shader, const Camera &camera);
        void PrepareEntity(Entity entity, Shader *shader, Camera camera);
        void UnbindTexturedModel();

    protected:
    private:
};

#endif // RENDERER_H
