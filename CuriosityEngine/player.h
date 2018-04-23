#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "entity.h"
#include "terrain.h"

class Player
{
public:
    Player(Entity *playerEntity);

    void Input(Terrain terrain);
    void Move(const glm::vec3& direction, float distance, Terrain terrain);
	void Fall();

    void SetPos( glm::vec3 pos ) { m_pos = pos; }
    void SetPosX( int x ) { m_pos.x = x; }
    void SetPosY( int y ) { m_pos.y = y; }
    void SetPosZ( int z ) { m_pos.z = z; }

    inline glm::vec3& GetPos() { return m_pos; }
    inline float GetPosX() { return m_pos.x; }
    inline float GetPosY() { return m_pos.y; }
    inline float GetPosZ() { return m_pos.z; }

    Entity *playerEntity;
protected:
private:
	bool isJumping;
	float yDestination;
	float yVelocity;
    glm::vec3 m_pos;
};

#endif // PLAYER_H
