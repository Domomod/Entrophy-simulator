#include "camera.h"
#include "input.h"
#include "mytime.h"
#include "vec3math.h"

#include <windows.h>
#include <string>

#include <iostream>

extern bool m_mouseLocked;
extern int camera_mode;
extern int camera_switch_cd;

const glm::vec3 Camera::UP(0,1,0);
const glm::vec3 Camera::DOWN(0,-1,0);
const glm::vec3 Camera::LEFT(-1,0,0);
const glm::vec3 Camera::RIGHT(1,0,0);
const glm::vec3 Camera::FORWARD(0,0,1);
const glm::vec3 Camera::BACK(0,0,-1);
const glm::vec3 Camera::ONE(1,1,1);
const glm::vec3 Camera::ZERO(0,0,0);
float returnRadiansf(float angle);


Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
    //TODO (user#1#): update perspective when window is resized
    m_perspective = glm::perspective(fov, aspect, zNear, zFar);
    m_position = pos;
    m_forward = glm::vec3( 0.0f, 0.0f ,1.0f );
    m_up = glm::vec3( 0.0f, 1.0f,0.0f );
	distToFocus = 50.0f;
}

void Camera::lookAt(const glm::vec3& fixedPoint)
{
    m_forward = glm::normalize(glm::vec3( fixedPoint.x - Camera::getPos().x,
                                          fixedPoint.y - Camera::getPos().y,
                                          fixedPoint.z - Camera::getPos().z));
    m_up = glm::vec3(0,1,0);
}

void Camera::follow(const glm::vec3& fixedPoint, glm::vec3 direction, float length)
{
    glm::vec3 dir = direction;
    dir = Vec3Math::getnormalized(dir);

    m_position = fixedPoint + ( dir * length);
}

void Camera::setPos(const glm::vec3& pos)
{

}

void Camera::setForward(const glm::vec3& forward)
{

}

void Camera::setUp(const glm::vec3& up)
{

}

void Camera::Input()
{
	float sensitivity = 0.018f;
    float movAmt = (float)(60 * MyTime::getDelta() );

    if(Input::getKey(KEY_ESCAPE))
	{
		Input::setCursor(true);
		m_mouseLocked = false;
	}

    if(camera_mode== FREE_CAM)
    {
        if(m_mouseLocked)
        {
            glm::vec2 centerPos = glm::vec2 (400.0f, 300.0f);
            glm::vec2 deltaPos = Input::getMousePosition()-centerPos;

            bool rotX=( deltaPos.y!= 0);
            bool rotY=( deltaPos.x!= 0);

            if(rotY)
            RotateY(deltaPos.x * sensitivity);
            if(rotX)
            RotateX(deltaPos.y * sensitivity);
            if(rotY || rotX)
            Input::setMousePosition(centerPos);
        }

        if(Input::getKey(KEY_W))
            Move(getForward(), movAmt);
        if(Input::getKey(KEY_S))
            Move(getForward(), -movAmt);
        if(Input::getKey(KEY_A))
            Move(getLeft(), movAmt);
        if(Input::getKey(KEY_D))
            Move(getRight(), movAmt);
		if (Input::getKey(KEY_SPACE))
			Move(getUp(), movAmt);
		if (Input::getKey(KEY_X))
			Move(getUp(), -movAmt);
    }

    if(camera_mode== THIRD_PERSON_CAM)
    {
		if (m_mouseLocked)
		{
			glm::vec2 centerPos = glm::vec2(400.0f, 300.0f);
			glm::vec2 deltaPos = Input::getMousePosition() - centerPos;

			bool rotX = (deltaPos.y != 0);
			bool rotY = (deltaPos.x != 0);

			if (rotY) {
				float angle = - deltaPos.x * sensitivity;
				normalToFocus = Vec3Math::rot(normalToFocus, angle, glm::vec3(0.0f, 1.0f, 0.0f));
			}
			if (rotX) {
				float angle = deltaPos.y * sensitivity;
				glm::vec3 axis = Vec3Math::cross(UP, m_forward);
				normalToFocus = Vec3Math::rot(normalToFocus, angle, axis);
			}
			if (rotY || rotX)
				Input::setMousePosition(centerPos);
		}
		follow(*focusPoint, normalToFocus, distToFocus);
		lookAt(*focusPoint);
    }

    if(Input::getMouseDown(LEFT_MOUSE))
	{
		glm::vec2 centerPos = glm::vec2(400.0f, 300.0f);
		Input::setMousePosition(centerPos);
		//Input::setCursor(false);
		m_mouseLocked = true;
	}
	if (Input::getWheelUp())
		distToFocus += -2.5f;
	if (Input::getWheelDown())
		distToFocus += 2.5f;
    if(Input::getKey(KEY_GRAVE) && camera_switch_cd==0)
    {
        camera_switch_cd=30;
        if(scene==1) scene =0;
        else
        if(scene ==0) scene =1;
    }
    if(camera_switch_cd>0)camera_switch_cd--;
}

void Camera::RotateX(float angle)
{
    glm::vec3 hAxis = Vec3Math::cross(UP, m_forward);
    Vec3Math::normalize(&hAxis);

    m_forward = Vec3Math::rot(m_forward, angle, hAxis);
    Vec3Math::normalize(&m_forward);

    m_up = Vec3Math::rot(m_up,angle, hAxis);
    Vec3Math::normalize(&m_up);

}

void Camera::RotateY(float angle)
{
    glm::vec3 hAxis = Vec3Math::cross(UP, m_forward);
    Vec3Math::normalize(&hAxis);

    m_forward = Vec3Math::rot(m_forward, -angle, UP);
    Vec3Math::normalize(&m_forward);
    m_up = Vec3Math::cross(m_forward, hAxis);
    Vec3Math::normalize(&m_up);
}

void Camera::Move(const glm::vec3& direction, float distance)
{
    glm::vec3 dir = direction;
    dir = Vec3Math::getnormalized(dir);
    m_position+= ( dir * distance);
}
