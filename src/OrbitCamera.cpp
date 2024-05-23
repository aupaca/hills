#include "OrbitCamera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

OrbitCamera::OrbitCamera(const glm::vec3& target, float radius)
{
	_yall = 0.f;
	_pitch = 0.f;
	_up = glm::vec3(0.f, 1.f, 0.f);
	_radius = radius;
	lookAt(target);
}

void OrbitCamera::lookAt(const glm::vec3& target)
{
	_target = target;
	_position.x = target.x + cosf(_yall) * cosf(_pitch) * _radius;
	_position.y = target.y + sinf(_pitch) * _radius;
	_position.z = target.z + sinf(_yall) * cosf(_pitch) * _radius;
	_direction = glm::normalize(target - _position);
}

void OrbitCamera::rotate(const glm::vec2& rotation)
{
	_yall += rotation.x;
	_pitch += rotation.y;
	
	if (_pitch > glm::radians(89.9f))
	{
		_pitch = glm::radians(89.9f);
	}
	else if (_pitch < glm::radians(-89.9f))
	{
		_pitch = glm::radians(-89.9f);
	}
	
	lookAt(_target);
}

glm::mat4 OrbitCamera::viewMatrix() const
{
	return glm::lookAt(_position, _position + _direction, _up);
}


