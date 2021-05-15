#pragma once
#include "../Camera/Camera.hpp"

// clang-format off
#include <glad/glad.h>
#include <GLFW/glfw3.h>
// clang-format on

#include <bitset>

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

class KeyboardHandler
{
private:
	static std::bitset<sizeof( Key )> m_keyMap;
	static std::bitset<sizeof( Key )> m_releaseMap;

public:
	static void Set( const Key& key, const bool& val );

	static void ProcessInput( GLFWwindow* window, const float& deltaTime );
};