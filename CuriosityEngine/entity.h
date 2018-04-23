#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texturedmodel.h"

class Entity
{
    public:
        Entity() {}

        Entity(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
        {
         m_model = model;
         m_position = position;
         m_rotX = rotX;
         m_rotY = rotY;
         m_rotZ = rotZ;
         m_scale = glm::vec3(scale);
        }

		Entity(TexturedModel model, glm::vec3 position, float rotX, float rotY, float rotZ, glm::vec3 scale)
		{
			m_model = model;
			m_position = position;
			m_rotX = rotX;
			m_rotY = rotY;
			m_rotZ = rotZ;
			m_scale = scale;
		}

        void increasePosition(float dx, float dy, float dz){
            this->m_position.x+=dx;
            this->m_position.y+=dy;
            this->m_position.z+=dz;
        }

        void increaseRotation(float dx, float dy, float dz){
            this->m_rotX+=dx;
            this->m_rotY+=dy;
            this->m_rotZ+=dz;
        }

        inline TexturedModel& GetModel () { return m_model; }
        inline void SetModel (TexturedModel model) { m_model = model; }

        inline glm::vec3& GetPos() { return m_position; }
        inline void SetPos(glm::vec3 position) { m_position = position; }
        inline glm::vec3 *GetPosAdr() { return &m_position; }

        inline float GetRotX() { return m_rotX; }
        inline void SetRotX(float rotX) { m_rotX = rotX; }

        inline float GetRotY() { return m_rotY; }
        inline void SetRotY(float rotY) { m_rotY = rotY; }

        inline float GetRotZ() { return m_rotZ; }
        inline void SetRotZ(float rotZ) { m_rotZ = rotZ; }

        inline glm::vec3 GetScale() { return m_scale; }
		inline void SetScale(float scale) { m_scale = glm::vec3(scale); }
		inline void SetScale(glm::vec3 scale) { m_scale = scale; }

        ~Entity();
    protected:
    private:
        TexturedModel m_model;
        glm::vec3 m_position;
        float m_rotX,m_rotY,m_rotZ;
        glm::vec3 m_scale;
};

#endif // ENTITY_H
