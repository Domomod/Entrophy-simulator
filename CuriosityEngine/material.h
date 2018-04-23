#ifndef MATERIAL_H
#define MATERIAL_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "texture.h"

class Material
{
public:
    Material()
    {

    }
    Material(	const glm::vec3& ambient, 
				const glm::vec3& diffuse, 
				const glm::vec3& specular, 
				const float shininess,
				const float dispMapScale = 0.0f,
				const float dispMapOffset = 0.0f,
				glm::vec3 emmision = glm::vec3(0.0f, 0.0f, 0.0f)	)
    {
        this->m_ambient = ambient;
        this->m_diffuse = diffuse;
        this->m_specular = specular;
        this->m_shininess = shininess;
        this->m_dispMapScale = dispMapScale;
        float baseBias = dispMapScale/2.0f;
        this->m_dispMapBias = -baseBias + baseBias * dispMapOffset;
		this->m_emmision = emmision;
    }
    const float *getShininess(){ return &m_shininess; }
	glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;
    float m_shininess;
    float m_dispMapScale;
    float m_dispMapBias;
	glm::vec3 m_emmision;
protected:
private:
};

#endif // MATERIAL_H
