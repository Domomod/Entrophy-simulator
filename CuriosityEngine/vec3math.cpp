#include "vec3math.h"
#include "my_math.h"
#include "quaternion.h"

#include <iostream>

glm::vec3 Vec3Math::translate(glm::vec3 a, glm::vec3 b)
{
    const float _x= a.x + b.x;
    const float _y= a.y + b.y;
    const float _z= a.z + b.z;

    return glm::vec3(_x, _y, _z);
}

glm::vec3 Vec3Math::cross(glm::vec3 a, glm::vec3 b)
{
    const float _x= a.y * b.z - a.z * b.y;
    const float _y=a.z * b.x - a.x * b.z;
    const float _z= a.x * b.y - a.y * b.x;

    return glm::vec3(_x, _y, _z);
}

glm::vec3 Vec3Math::rot(glm::vec3 a, float angle, glm::vec3 axe)
{
    const float sinHalfAngle = sinf(My_Math::returnRadiansf(angle / 2));
    const float cosHalfAngle = cosf(My_Math::returnRadiansf(angle / 2));

    const float Rx = axe.x * sinHalfAngle;
    const float Ry = axe.y * sinHalfAngle;
    const float Rz = axe.z * sinHalfAngle;
    const float Rw = cosHalfAngle;

    Quaternion rotationQ(Rx, Ry, Rz, Rw);

    Quaternion conjugateQ = rotationQ.conjugate();
    conjugateQ.normalize();
    Quaternion w = rotationQ * a *conjugateQ;

	glm::vec3 ret(w.x, w.y, w.z);

    return ret;
}

void Vec3Math::normalize(glm::vec3 *a)
{
    const float length = sqrt(((*a).x * (*a).x) + ((*a).y * (*a).y) + ((*a).z * (*a).z));
    (*a).x /= length;
    (*a).y /= length;
    (*a).z /= length;
}

glm::vec3 Vec3Math::getnormalized(glm::vec3 a)
{
    const float length = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    a /= length;

    return a;
}

float Vec3Math::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
    float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
    float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
    float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
    float l3 = 1.0f - l1 - l2;
    return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}
