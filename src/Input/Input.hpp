#pragma once
// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <bitset>
#include <iostream>

#include "../Camera/Camera.hpp"
enum Key : short // Enum to hold different key presses (Stored as GLFW keys)
{
	ESC		= GLFW_KEY_ESCAPE,
	SPACE	= GLFW_KEY_SPACE,
	L_SHIFT = GLFW_KEY_LEFT_SHIFT,
	L_CTRL	= GLFW_KEY_LEFT_CONTROL,
	L_ALT	= GLFW_KEY_LEFT_ALT,

	Q = GLFW_KEY_Q,
	W = GLFW_KEY_W,
	E = GLFW_KEY_E,
	R = GLFW_KEY_R,
	T = GLFW_KEY_T,
	Y = GLFW_KEY_Y,
	U = GLFW_KEY_U,
	I = GLFW_KEY_I,
	O = GLFW_KEY_O,
	P = GLFW_KEY_P,
	A = GLFW_KEY_A,
	S = GLFW_KEY_S,
	D = GLFW_KEY_D,
	F = GLFW_KEY_F,
	G = GLFW_KEY_G,
	H = GLFW_KEY_H,
	J = GLFW_KEY_J,
	K = GLFW_KEY_K,
	L = GLFW_KEY_L,
	Z = GLFW_KEY_Z,
	X = GLFW_KEY_X,
	C = GLFW_KEY_C,
	V = GLFW_KEY_V,
	B = GLFW_KEY_B,
	N = GLFW_KEY_N,
	M = GLFW_KEY_M,

	N0 = GLFW_KEY_0,
	N1 = GLFW_KEY_1,
	N2 = GLFW_KEY_2,
	N3 = GLFW_KEY_3,
	N4 = GLFW_KEY_4,
	N5 = GLFW_KEY_5,
	N6 = GLFW_KEY_6,
	N7 = GLFW_KEY_7,
	N8 = GLFW_KEY_8,
	N9 = GLFW_KEY_9,

	F1	= GLFW_KEY_F1,
	F2	= GLFW_KEY_F2,
	F3	= GLFW_KEY_F3,
	F4	= GLFW_KEY_F4,
	F5	= GLFW_KEY_F5,
	F6	= GLFW_KEY_F6,
	F7	= GLFW_KEY_F7,
	F8	= GLFW_KEY_F8,
	F9	= GLFW_KEY_F9,
	F10 = GLFW_KEY_F10,
	F11 = GLFW_KEY_F11,
	F12 = GLFW_KEY_F12
};

static double		fpsCount	= 0;
static bool			countingFPS = false;
static unsigned int frameCount	= 0;

class KeyboardHandler
{
private:
	std::bitset<sizeof( Key )> keyMap;
	std::bitset<sizeof( Key )> releasedMap;

public:
	KeyboardHandler() : keyMap( 0 ), releasedMap( 0 ) {}

	void Set( Key key, bool val )
	{
		keyMap[key] = val;
	}

	void ProcessInput( GLFWwindow* window, float deltaT )
	{
		// When escape is pressed, close the window
		if ( keyMap[Key::ESC] )
			glfwSetWindowShouldClose( window, true );

		// When the shift key is down make the camera move faster
		if ( keyMap[Key::L_SHIFT] )
		{
			if ( !cam.movingFast ) // Check if it's not already marked as moving fast
				cam.movingFast = true;
		}
		else if ( cam.movingFast ) // Check if it's marked as moving fast but key isn't pressed
			cam.movingFast = false;

		// Display the fps
		if ( keyMap[Key::F1] )
		{
			fpsCount += deltaT;
			frameCount++;

			if ( !countingFPS )
				countingFPS = true;
		}
		else if ( countingFPS )
		{
			countingFPS = false;
			std::cout << std::endl;
			std::cout << "Averaged " << frameCount / fpsCount << " FPS over " << frameCount << " frames" << std::endl;

			frameCount = 0;
			fpsCount   = 0;
		}

		// Camera movement
		if ( keyMap[Key::W] )
			cam.ProcessKeyboard( CameraMovement::FORWARD, deltaT );
		if ( keyMap[Key::A] )
			cam.ProcessKeyboard( CameraMovement::LEFT, deltaT );
		if ( keyMap[Key::S] )
			cam.ProcessKeyboard( CameraMovement::BACKWARD, deltaT );
		if ( keyMap[Key::D] )
			cam.ProcessKeyboard( CameraMovement::RIGHT, deltaT );
		if ( keyMap[Key::SPACE] )
			cam.ProcessKeyboard( CameraMovement::UP, deltaT );
		if ( keyMap[Key::L_CTRL] )
			cam.ProcessKeyboard( CameraMovement::DOWN, deltaT );
	}
};

KeyboardHandler kb = KeyboardHandler();