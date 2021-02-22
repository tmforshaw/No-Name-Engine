#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Define the ways the camera can move
enum class CameraMovement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
private:
	glm::vec3 worldUp;

	// Camera's transform variables
	glm::vec2 rotation;
	glm::vec3 position;

public:
	// Properties
	float moveSpeed;
	float moveSpeedFast;
	float mouseSensitivity;
	float zoomSensitivity;
	float fov;

	bool movingFast;

	// Axis
	glm::vec3 zDirection;
	glm::vec3 xDirection;
	glm::vec3 yDirection;

	// Instantiation function
	Camera( glm::vec3 pos = glm::vec3( 0.0f, 20.0f, 0.0f ), glm::vec2 rot = glm::vec2( glm::radians( 45.0f ), 0.0f ) );

	// User input functions
	void ProcessKeyboard( CameraMovement dir, float deltaT );
	void ProcessMouse( float xOff, float yOff );
	void ProcessMouseScroll( float yOff );

	// Matrix to convert from world coords to view coords
	glm::mat4 GetViewMatrix();

	glm::vec3 GetPos();

private:
	// Update all of the camera's axis and rotations
	void UpdateVectors();
};

// Instantiate the camera
extern Camera cam;