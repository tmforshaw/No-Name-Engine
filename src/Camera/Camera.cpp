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

// Instantiate the camera
Camera cam( { 0.0f, 20.0f, 0.0f } );

Camera::Camera( glm::vec3 pos, glm::vec2 rot )
	: mouseSensitivity( mouseSens ), moveSpeed( mSpeed ), moveSpeedFast( mSpeedFast ), worldUp( glm::vec3( 0.0f, 1.0f, 0.0f ) ), zoomSensitivity( zoomSens ), fov( fovDefault ), movingFast( false )
{
	// Set the initial position and rotation
	position = pos;
	rotation = rot;

	// Update the camera's axis
	UpdateVectors();
}

void Camera::ProcessKeyboard( CameraMovement dir, float deltaT )
{
	// Define the velocity the camera is moving at
	float velocity = ( movingFast ? moveSpeedFast : moveSpeed ) * deltaT;

	// Move in the correct direction based upon the input direction
	switch ( dir )
	{
	case CameraMovement::FORWARD:
		position += zDirection * velocity;
		break;
	case CameraMovement::BACKWARD:
		position -= zDirection * velocity;
		break;
	case CameraMovement::RIGHT:
		position += xDirection * velocity;
		break;
	case CameraMovement::LEFT:
		position -= xDirection * velocity;
		break;
	case CameraMovement::UP:
		position += worldUp * velocity;
		break;
	case CameraMovement::DOWN:
		position -= worldUp * velocity;
		break;
	default:
		break;
	}
}

void Camera::ProcessMouse( float xOff, float yOff )
{
	// Dampen or strengthen the mouse input to a reasonable level
	xOff *= mouseSensitivity;
	yOff *= mouseSensitivity;

	// Add the adjusted offsets to the rotation
	rotation.x += xOff;
	rotation.y += yOff;

	// Update the axis of the camera (Also ensures that the rotation is clamped)
	UpdateVectors();
}

void Camera::ProcessMouseScroll( float yOff )
{
	// Reduce the field of view when the user scrolls (adjusted to make it easier/harder)
	fov -= yOff * zoomSensitivity;

	// Clamp the FOV so that the camera is still usable
	if ( fov < minFOV )
		fov = minFOV;
	else if ( fov > maxFOV )
		fov = maxFOV;
}

glm::mat4 Camera::GetViewMatrix()
{
	// Use the LookAt matrix to move and rotate the camera
	return glm::lookAt( position, position + zDirection, worldUp );
}

glm::vec3 Camera::GetPos()
{
	return position;
}

void Camera::UpdateVectors()
{
	// Fix yaw by removing the remainder (modulo 2 pi)
	rotation.x = glm::mod( rotation.x, glm::pi<float>() * 2.0f );

	// Constrain pitch
	if ( rotation.y > glm::radians( 89.0f ) )
		rotation.y = glm::radians( 89.0f );
	if ( rotation.y < glm::radians( -89.0f ) )
		rotation.y = glm::radians( -89.0f );

	// Set new direction
	zDirection = glm::vec3(
		cos( rotation.x ) * cos( rotation.y ),
		sin( rotation.y ),
		sin( rotation.x ) * cos( rotation.y ) );

	// Normalise it
	zDirection = glm::normalize( zDirection );

	// Recalculate axis
	xDirection = glm::normalize( glm::cross( zDirection, worldUp ) );
	yDirection = glm::normalize( glm::cross( xDirection, zDirection ) );
}