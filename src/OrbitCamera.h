#ifndef ORBIT_CAMERA_H
#define ORBIT_CAMERA_H
#include <glm/glm.hpp>

class OrbitCamera
{
public:
	OrbitCamera(const glm::vec3& target, float radius);
	
	void lookAt(const glm::vec3& target);
	void rotate(const glm::vec2& rotation);
	const glm::vec3& direction() const;
	float radius() const;
	glm::mat4 viewMatrix() const;
	
private:
	glm::vec3 _position;
	glm::vec3 _direction;
	glm::vec3 _up;
	glm::vec3 _target;
	float _radius;
	float _yall;
	float _pitch;
};

inline const glm::vec3& OrbitCamera::direction() const
{
	return _direction;
}

inline float OrbitCamera::radius() const
{
	return _radius;
}

#endif

