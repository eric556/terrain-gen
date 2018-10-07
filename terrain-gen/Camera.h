#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


class Camera
{
public:
	Camera();
	void Move(glm::vec3 direction);
	void RotateX(float angle);
	void RotateY(float angle);
	void RotateZ(float angle);

	void MoveForward(float distance);
	void MoveUpward(float distance);
	void StrafeRight(float distance);
	glm::mat4 GetViewMatrix();
	glm::vec3 GetPosition();

private:
	glm::vec3 m_ViewDir;
	glm::vec3 m_RightVec;
	glm::vec3 m_UpVec;
	glm::vec3 m_Position;
	const float PI = 3.14159265359;

	float m_RotatedX, m_RotatedY, m_RotatedZ;
};