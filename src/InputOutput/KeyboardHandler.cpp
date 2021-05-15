#include "KeyboardHandler.hpp"

std::bitset<sizeof( Key )> KeyboardHandler::m_keyMap;
std::bitset<sizeof( Key )> KeyboardHandler::m_releaseMap;

void KeyboardHandler::Set( const Key& key, const bool& val )
{
	m_keyMap[key] = val;
}

void KeyboardHandler::ProcessInput( GLFWwindow* window, const float& deltaTime )
{
	// When escape is pressed, close the window
	if ( m_keyMap[Key::ESC] )
		glfwSetWindowShouldClose( window, true );

	// When the shift key is down make the camera move faster
	if ( m_keyMap[Key::L_SHIFT] )
	{
		if ( !Camera::m_movingFast ) // Check if it's not already marked as moving fast
			Camera::m_movingFast = true;
	}
	else if ( Camera::m_movingFast ) // Check if it's marked as moving fast but key isn't pressed
		Camera::m_movingFast = false;

	// // Display the fps
	// if ( m_keyMap[Key::F1] )
	// {
	// 	fpsCount += deltaTime;
	// 	frameCount++;

	// 	if ( !countingFPS )
	// 		countingFPS = true;
	// }
	// else if ( countingFPS )
	// {
	// 	countingFPS = false;
	// 	std::cout << std::endl;
	// 	std::cout << "Averaged " << frameCount / fpsCount << " FPS over " << frameCount << " frames" << std::endl;

	// 	frameCount = 0;
	// 	fpsCount   = 0;
	// }

	// Camera movement
	if ( m_keyMap[Key::W] )
		Camera::ProcessKeyboard( CameraMovement::FORWARD, deltaTime );
	if ( m_keyMap[Key::A] )
		Camera::ProcessKeyboard( CameraMovement::LEFT, deltaTime );
	if ( m_keyMap[Key::S] )
		Camera::ProcessKeyboard( CameraMovement::BACKWARD, deltaTime );
	if ( m_keyMap[Key::D] )
		Camera::ProcessKeyboard( CameraMovement::RIGHT, deltaTime );
	if ( m_keyMap[Key::SPACE] )
		Camera::ProcessKeyboard( CameraMovement::UP, deltaTime );
	if ( m_keyMap[Key::L_CTRL] )
		Camera::ProcessKeyboard( CameraMovement::DOWN, deltaTime );
}