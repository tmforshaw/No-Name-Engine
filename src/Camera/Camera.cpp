#include "Camera.hpp"

#include <iostream>

// Default values
#define mSpeed	   10.0f
#define mSpeedFast 25.0f
#define mouseSens  0.005f
#define zoomSens   5.0f
#define fovDefault 45.0f

#define minFOV 1.0f
#define maxFOV 75.0f

// Initialise all the camera variables

// Movement
float	  Camera::m_moveSpeed	  = mSpeed;
float	  Camera::m_moveSpeedFast = mSpeedFast;
bool	  Camera::m_movingFast	  = false;
glm::vec2 Camera::m_rotation;
glm::vec3 Camera::m_position;

// Mouse
float Camera::m_zoomSensitivity	 = zoomSens;
float Camera::m_fov				 = fovDefault;
float Camera::m_mouseSensitivity = mouseSens;

// Axes
glm::vec3 Camera::m_worldUp = glm::vec3( 0.0f, 1.0f, 0.0f );
glm::vec3 Camera::m_zDirection;
glm::vec3 Camera::m_xDirection;
glm::vec3 Camera::m_yDirection;

// View projection
glm::mat4 Camera::m_view;

void Camera::Instantiate( const glm::vec3& pos, const glm::vec2& rot )
{
	// Set the initial position and rotation
	glm::vec3 m_position = glm::vec3( -10.0f, -10.0f, 0.0f );
	glm::vec2 m_rotation = rot;

	// Update the camera's axis
	UpdateVectors();
}

void Camera::ProcessKeyboard( const CameraMovement& dir, const float& deltaT )
{
	// Define the velocity the camera is moving at
	float velocity = ( m_movingFast ? m_moveSpeedFast : m_moveSpeed ) * deltaT;

	// Move in the correct direction based upon the input direction
	switch ( dir )
	{
	case CameraMovement::FORWARD:
		m_position += m_zDirection * velocity;
		break;
	case CameraMovement::BACKWARD:
		m_position -= m_zDirection * velocity;
		break;
	case CameraMovement::RIGHT:
		m_position += m_xDirection * velocity;
		break;
	case CameraMovement::LEFT:
		m_position -= m_xDirection * velocity;
		break;
	case CameraMovement::UP:
		m_position += m_worldUp * velocity;
		break;
	case CameraMovement::DOWN:
		m_position -= m_worldUp * velocity;
		break;
	default:
		break;
	}

	// Use the LookAt matrix to move and rotate the camera
	m_view = glm::lookAt( m_position, m_position + m_zDirection, m_worldUp );
}

void Camera::ProcessMouse( const float& xOff, const float& yOff )
{
	// Dampen or strengthen the mouse input to a reasonable level and add to the rotation
	m_rotation.x += xOff * m_mouseSensitivity;
	m_rotation.y += yOff * m_mouseSensitivity;

	// Update the axis of the camera (Also ensures that the rotation is clamped)
	UpdateVectors();
}

void Camera::ProcessMouseScroll( const float& yOff )
{
	// Reduce the field of view when the user scrolls (adjusted to make it easier/harder)
	m_fov -= yOff * m_zoomSensitivity;

	// Clamp the FOV so that the camera is still usable
	if ( m_fov < minFOV )
		m_fov = minFOV;
	else if ( m_fov > maxFOV )
		m_fov = maxFOV;
}

glm::mat4 Camera::GetViewMatrix()
{
	return m_view;
}

glm::vec3 Camera::GetPos()
{
	return m_position;
}

void Camera::UpdateVectors()
{
	// Fix yaw by removing the remainder (modulo 2 pi)
	m_rotation.x = glm::mod( m_rotation.x, glm::pi<float>() * 2.0f );

	// Constrain pitch
	if ( m_rotation.y > glm::radians( 89.0f ) )
		m_rotation.y = glm::radians( 89.0f );
	if ( m_rotation.y < glm::radians( -89.0f ) )
		m_rotation.y = glm::radians( -89.0f );

	// Set new direction
	m_zDirection = glm::vec3(
		cos( m_rotation.x ) * cos( m_rotation.y ),
		sin( m_rotation.y ),
		sin( m_rotation.x ) * cos( m_rotation.y ) );

	// Normalise it
	m_zDirection = glm::normalize( m_zDirection );

	// Recalculate axis
	m_xDirection = glm::normalize( glm::cross( m_zDirection, m_worldUp ) );
	m_yDirection = glm::normalize( glm::cross( m_xDirection, m_zDirection ) );

	// Use the LookAt matrix to move and rotate the camera
	m_view = glm::lookAt( m_position, m_position + m_zDirection, m_worldUp );
}