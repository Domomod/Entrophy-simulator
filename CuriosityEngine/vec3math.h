#ifndef VEC3MATH_H
#define VEC3MATH_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Vec3Math
{
public:

    static glm::vec3 translate(glm::vec3 a, glm::vec3 b);
    static glm::vec3 cross(glm::vec3 a, glm::vec3 b);
    static glm::vec3 rot(glm::vec3 a, float angle, glm::vec3 b);
    static void normalize( glm::vec3 *a);
    static glm::vec3 getnormalized(glm::vec3 a);
    static float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);

protected:

private:
};

#endif // VEC3MATH_H
