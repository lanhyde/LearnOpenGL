#include "pch.h"
#include "Camera.h"

Camera::Camera()
{
	
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	movementSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	Update();
}

void Camera::Update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

void Camera::KeyControl(bool* keys, GLfloat deltaTime)
{
	if(keys[GLFW_KEY_W])
	{
		position += front * movementSpeed * deltaTime;
	}
	if(keys[GLFW_KEY_S])
	{
		position -= front * movementSpeed * deltaTime;
	}
	if(keys[GLFW_KEY_A])
	{
		position -= right * movementSpeed * deltaTime;
	}
	if(keys[GLFW_KEY_D])
	{
		position += right * movementSpeed * deltaTime;
	}
}

glm::mat4 Camera::CalculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::MouseControl(GLfloat deltaX, GLfloat deltaY)
{
	deltaX *= turnSpeed;
	deltaY *= turnSpeed;

	yaw += deltaX;
	pitch += deltaY;

	if(pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if(pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	Update();
}



Camera::~Camera()
{
}
