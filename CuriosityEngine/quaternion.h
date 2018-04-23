#ifndef QUATERNION_H
#define QUATERNION_H

#include <glm/glm.hpp>

class Quaternion
{
public:
    float x, y, z, w;

    Quaternion(float _x, float _y, float _z, float _w);

    void normalize();
	glm::vec3 xyz() { return glm::vec3(x, y, z); }
    Quaternion conjugate();

	Quaternion operator*(const Quaternion& r);
	Quaternion operator*(const glm::vec3& v);
 };



#endif
