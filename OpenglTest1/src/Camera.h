#pragma once

#include"glm/glm.hpp"
#include"glm//gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::vec3 cameraRight;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
public:
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up= glm::vec3(0.0f, 1.0f, 0.0f),float yaw = YAW, float pitch = PITCH);
	
	~Camera();
	inline glm::mat4 GetViewMat() const {
		return glm::lookAt(cameraPos,cameraPos+cameraFront, cameraUp);
	}
	void CameraMove(Camera_Movement direction, float delateTime);
	void CameraMouseView(float xoffset, float yoffset);

	void CameraScroll(float yoffset);

private:
	void UpDateCamer();
};





