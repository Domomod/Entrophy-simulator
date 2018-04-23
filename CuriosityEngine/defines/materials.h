#ifndef MATERIALS_H
#define MATERIALS_H

//#include "../entitiesdefine.h" // <- pozwala na includowanie z innych subfolderow
#include "../material.h"

static Material simple (
    glm::vec3(0.2f, 0.2f, 0.2f),
    glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    6.0f,
    0.0f,
    0.0f
    );
#endif // MATERIALS_H