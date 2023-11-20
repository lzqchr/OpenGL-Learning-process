#include "Camera.h"

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f), MouseSensitivity(0.1f), Zoom(45.0f)
{
	cameraPos = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	UpDateCamer();
}



Camera::Camera(glm::vec3 position , glm::vec3 up, float yaw , float pitch)
	: cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
{
	cameraPos = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	UpDateCamer();
}

Camera::~Camera()
{
	
}

void Camera::CameraMove(Camera_Movement direction, float delateTime)
{
	float velocity = MovementSpeed * delateTime;
	if (direction == FORWARD)
		cameraPos += cameraFront * velocity;
	if (direction == BACKWARD)
		cameraPos -= cameraFront * velocity;
	if (direction == LEFT)
		cameraPos -= cameraRight * velocity;
	if (direction == RIGHT)
		cameraPos += cameraRight * velocity;
}

void Camera::CameraMouseView(float xoffset, float yoffset)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	//·ÀÖ¹¸©Ñö½Ç¹ýÍ·
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	UpDateCamer();
}
void Camera::CameraScroll(float yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}


void Camera::UpDateCamer()
{
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));

	cameraFront = glm::normalize(front);

	cameraRight = glm::normalize( glm::cross(cameraFront, WorldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
