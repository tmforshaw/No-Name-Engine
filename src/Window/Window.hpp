#pragma once
// clang-format off
#include <glad/glad.h> // GLAD must be before GLFW
#include <GLFW/glfw3.h>
// clang-format on

class Window
{
private:
	int			 m_pos[2];
	int			 m_size[2];
	GLFWwindow*	 m_window;
	GLFWmonitor* m_monitor;

	// Mouse variables
	static float m_prevMouseX, m_prevMouseY;
	static bool	 m_firstMouse;

	static void CallbackResize( GLFWwindow* p_window, int dx, int dy );
	static void CallbackKeyboard( GLFWwindow* window, int key, int scancode, int action, int mods );
	static void CallbackMouse( GLFWwindow* window, double xPos, double yPos );
	static void CallbackScroll( GLFWwindow* window, double xOff, double yOff );

	void Resize();

public:
	Window( const unsigned short& p_width, const unsigned short& p_height, const char* p_title );

	void SetFullscreen( bool fullscreen = true );

	void MainLoop();
};