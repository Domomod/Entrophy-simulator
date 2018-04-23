#ifndef LIGHT_H
#define LIGHT_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define MAX_LIGHTS 64

enum
{
	DIRECTIONAL_LIGHT,
	POINT_LIGHT,
	SPOT_LIGHT
};

class Light {
public:
	Light(int type, glm::vec3 position, float constantAtt, float linearAtt,
		float quadraticAtt, glm::vec3 color, float ambientCoefficient, glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f))
    {
		this->m_type = type;
		this->m_position = position;
		this->m_attunation = glm::vec3(constantAtt, linearAtt, quadraticAtt);
		this->m_direction = direction;
		this->m_color = color;
		this->m_ambientCoefficient = ambientCoefficient;
    }
    ~Light();

	int m_type;
	glm::vec3 m_position;
	glm::vec3 m_attunation;
	glm::vec3 m_direction;
	glm::vec3 m_color;
	float m_ambientCoefficient;
};

#endif // LIGHT_H
