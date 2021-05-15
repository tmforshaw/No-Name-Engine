#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
	static glm::vec3 m_worldUp;

	// Camera's transform variables
	static glm::vec2 m_rotation;
	static glm::vec3 m_position;

	static glm::mat4 m_view;

public:
	// Properties
	static float m_moveSpeed;
	static float m_moveSpeedFast;
	static bool	 m_movingFast;

	static float m_mouseSensitivity;
	static float m_zoomSensitivity;
	static float m_fov;

	// Axis
	static glm::vec3 m_zDirection;
	static glm::vec3 m_xDirection;
	static glm::vec3 m_yDirection;

	// Instantiation function
	static void Instantiate( const glm::vec3& pos = glm::vec3( 0.0f, 0.0f, 0.0f ), const glm::vec2& rot = glm::vec2( glm::radians( 45.0f ), 0.0f ) );

	// User input functions
	static void ProcessKeyboard( const CameraMovement& dir, const float& deltaT );
	static void ProcessMouse( const float& xOff, const float& yOff );
	static void ProcessMouseScroll( const float& yOff );

	// Matrix to convert from world coords to view coords
	static glm::mat4 GetViewMatrix();

	static glm::vec3 GetPos();

private:
	// Update all of the camera's axis and rotations
	static void UpdateVectors();
};