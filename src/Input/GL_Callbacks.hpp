#pragma once
#include "../Constants.hpp"
#include "Input.hpp"

#include <glad/glad.h>

// Mouse variables
static float prevMouseX = width / 2, prevMouseY = height / 2;
static bool	 firstMouse = true;

// Resize the viewport when the user resizes the window
void ResizeViewportCallback( GLFWwindow* window, int n_width, int n_height )
{
	width  = n_width;
	height = n_height;
	glViewport( 0, 0, n_width, n_height );
}

void KeyboardCallback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
	// Escape Key
	if ( key == Key::ESC )
		if ( action == GLFW_PRESS )
			kb.Set( Key::ESC, true );
		else if ( action == GLFW_RELEASE )
			kb.Set( Key::ESC, false );

	// Left Shift
	if ( key == Key::L_SHIFT )
		if ( action == GLFW_PRESS )
			kb.Set( Key::L_SHIFT, true );
		else if ( action == GLFW_RELEASE )
			kb.Set( Key::L_SHIFT, false );

	// F1 Key
	if ( key == Key::F1 )
		if ( action == GLFW_PRESS )
			kb.Set( Key::F1, true );
		else if ( action == GLFW_RELEASE )
			kb.Set( Key::F1, false );

	// Camera movement

	// Forward
	if ( key == Key::W )
		if ( action == GLFW_PRESS )
			kb.Set( Key::W, true );
		else if ( action == GLFW_RELEASE )
			kb.Set( Key::W, false );

	// Left
	if ( key == Key::A )
		if ( action == GLFW_PRESS )
			kb.Set( Key::A, true );
		else if ( action == GLFW_RELEASE )
			kb.Set( Key::A, false );

	// Back
	if ( key == Key::S )
		if ( action == GLFW_PRESS )
			kb.Set( Key::S, true );
		else if ( action == GLFW_RELEASE )
			kb.Set( Key::S, false );

	// Right
	if ( key == Key::D )
		if ( action == GLFW_PRESS )
			kb.Set( Key::D, true );
		else if ( action == GLFW_RELEASE )
			kb.Set( Key::D, false );

	// Up
	if ( key == Key::SPACE )
		if ( action == GLFW_PRESS )
			kb.Set( Key::SPACE, true );
		else if ( action == GLFW_RELEASE )
			kb.Set( Key::SPACE, false );

	// Down
	if ( key == Key::L_CTRL )
		if ( action == GLFW_PRESS )
			kb.Set( Key::L_CTRL, true );
		else if ( action == GLFW_RELEASE )
			kb.Set( Key::L_CTRL, false );
}

void MouseCallback( GLFWwindow* window, double xPos, double yPos )
{
	if ( firstMouse )
	{
		prevMouseX = xPos;
		prevMouseY = yPos;
		firstMouse = false;
	}

	float xOff = xPos - prevMouseX;
	float yOff = prevMouseY - yPos; // Reverse because y-axis is from bottom to top
	prevMouseX = xPos;
	prevMouseY = yPos;

	cam.ProcessMouse( xOff, yOff );
}

void ScrollCallback( GLFWwindow* window, double xOff, double yOff )
{
	cam.ProcessMouseScroll( (float)yOff );
}