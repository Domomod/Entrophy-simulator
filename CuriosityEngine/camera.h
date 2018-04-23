#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "vec3math.h"
#include "quaternion.h"

class Camera
{
public:
    Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

    inline glm::mat4 GetViewProjection() const
    {
        //view times projection
        return m_perspective * glm::lookAt(m_position, m_position + m_forward, m_up);
    }

    inline glm::mat4 GetViewMatrix() const
    {
        //view times projection
        return glm::lookAt(m_position, m_position + m_forward, m_up);
    }

    //TODO::Create VectorClass:
    static const glm::vec3 UP;
	static const glm::vec3 DOWN;
	static const glm::vec3 LEFT;
	static const glm::vec3 RIGHT;
	static const glm::vec3 FORWARD;
	static const glm::vec3 BACK;
	static const glm::vec3 ONE;
	static const glm::vec3 ZERO;
	//

	inline glm::vec3 getPos() const
    {
        return m_position;
    }

    inline glm::vec3 getForward() const
    {
        return m_forward;
    }

    inline glm::vec3 getUp() const
    {
        return m_up;
    }

    inline glm::vec3 getLeft() const
    {
        return Vec3Math::cross(m_up, m_forward);
    }

    inline glm::vec3 getRight() const
    {
        return Vec3Math::cross(m_forward, m_up);
    }

    void setFocusPoint(glm::vec3 *point)
    {
        focusPoint = point;
    }

    void lookAt(const glm::vec3 &fixedPoint);
    void follow(const glm::vec3& fixedPoint, glm::vec3 direction, float length);
    void setPos(const glm::vec3& pos);
	void setForward(const glm::vec3& forward);
	void setUp(const glm::vec3& up);

    void Input();
    void RotateX(float angle);
    void RotateY(float angle);
    void Move(const glm::vec3& direction, float distance);

	int scene = 0;
protected:
private:
    glm::mat4 m_perspective;
    glm::vec3 m_position;
    glm::vec3 m_forward;
    glm::vec3 m_up;

    enum
    {
        FREE_CAM,
        THIRD_PERSON_CAM,

        NUM_CAMERA_TYPES
    };

    glm::vec3 *focusPoint;
	float distToFocus;
	glm::vec3 normalToFocus = glm::vec3(-1.0f, 1.0f, -1.0f);
	Quaternion focusRotation = Quaternion(1.0f ,0.0f ,0.0f, 30.0f);
};

#endif // CAMERA_H
