#include "player.h"
#include "camera.h"
#include "input.h"
#include "mytime.h"
#include "vec3math.h"

extern bool m_mouseLocked;
extern glm::vec3 playerForward;
extern glm::vec3 playerUp;
extern int camera_mode;

Player::Player(Entity *playerEntity)
{
    m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	isJumping = false;
	yDestination = 0.0f;
	yVelocity = 0.0f;
    this->playerEntity = playerEntity;
}

void Player::Move(const glm::vec3& direction, float distance, Terrain terrain)
{
	glm::vec3 dir = direction;
	dir = Vec3Math::getnormalized(dir) * distance;
	m_pos.x += dir.x;
	m_pos.z += dir.z;
	yDestination = terrain.GetHeight(m_pos.x, m_pos.z);
	if (!isJumping)
		m_pos.y = yDestination;
}

void Player::Input(Terrain terrain)
{
	float sensitivity = 0.18f;
    float movAmt = (float)(60 * MyTime::getDelta() );

    if(m_mouseLocked && camera_mode== 1)
	{
            if(Input::getKey(KEY_W))
                Move(playerForward, movAmt, terrain);
            if(Input::getKey(KEY_S))
                Move(playerForward, -movAmt, terrain);
            if(Input::getKey(KEY_A))
                Move(Vec3Math::cross(playerForward, glm::vec3(0,1,0)), -movAmt, terrain);
            if(Input::getKey(KEY_D))
                Move(Vec3Math::cross(playerForward, glm::vec3(0,1,0)), movAmt, terrain);
			if (Input::getKey(KEY_SPACE) && !isJumping){
				isJumping = true;
				yVelocity = 50.0f;
			}
			if (isJumping) {
				double t = MyTime::getDelta();
				float g = 98.1f;
				m_pos.y += yVelocity * t - g * t * t;
				yVelocity -= g * t;
				if (yDestination > m_pos.y) {
					yVelocity = 0.0f;
					m_pos.y = yDestination;
					isJumping = false;
				}
			}
            playerEntity->SetPos(m_pos);
        }
}

void Player::Fall()
	{
	}

