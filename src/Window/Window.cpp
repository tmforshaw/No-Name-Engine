#include "Window.hpp"

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_impl_glfw.h"
#include "../../dependencies/imgui/imgui_impl_opengl3.h"
#include "../Buffers/IndexBuffer.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Buffers/VertexBuffer.hpp"
#include "../InputOutput/KeyboardHandler.hpp"
#include "../Renderer/Renderer.hpp"
#include "../Scenes/MainScene.hpp"
#include "../Shader/Shader.hpp"
#include "../Texture/Texture.hpp"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

float Window::m_prevMouseX, Window::m_prevMouseY;
bool  Window::m_firstMouse = true;

Window::Window( const unsigned short& p_width, const unsigned short& p_height, const char* p_title )
{
	std::cout << "\nCreating an OpenGL window (" << p_width << "px x " << p_height << "px)\n\n";

	// Initialise GLFW
	glfwInit();

	// Configure GLFW
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );				 // OpenGL Version 4.x
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 6 );				 // OpenGL Version x.6
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // Force to use modern OpenGL

	// Create a window (Specify primary monitor to enable fullscreen)
	m_window = glfwCreateWindow( p_width, p_height, p_title, nullptr, nullptr ); // glfwGetPrimaryMonitor()
	if ( m_window == nullptr )
	{
		std::cout << "ERROR::GLFW::UNINITIALISED" << std::endl;
		glfwTerminate(); // Close the window
	}

	// Set the window as the context
	glfwMakeContextCurrent( m_window );

	// Allows the use of this Window class instead of a GLFWwindow
	glfwSetWindowUserPointer( m_window, this );

	// GLFW input callbacks
	glfwSetWindowSizeCallback( m_window, CallbackResize ); // Window resizing
	glfwSetKeyCallback( m_window, CallbackKeyboard );	   // Keyboard key
	glfwSetCursorPosCallback( m_window, CallbackMouse );   // Monitor mouse
	glfwSetScrollCallback( m_window, CallbackScroll );	   // Monitor Scrolling

	// Get the primary monitor
	m_monitor = glfwGetPrimaryMonitor();

	// Set the position variables
	glfwGetWindowPos( m_window, &m_pos[0], &m_pos[1] );

	// Set the size variables
	glfwGetWindowSize( m_window, &m_size[0], &m_size[1] );

	// Set the previous mouse position
	m_prevMouseX = m_size[0] / 2;
	m_prevMouseY = m_size[0] / 2;

	// Load the address of the OpenGL function pointers using GLAD (OS specific)
	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
		std::cout
			<< "ERROR::GLFW::UNINITIALISED" << std::endl;
	else
		std::cout << "Initialised GLAD\n\n";

	// Log the OpenGL version
	std::cout << "OpenGL Version " << glGetString( GL_VERSION ) << "\n\n";

	// Hide the cursor and capture it into the window
	glfwSetInputMode( m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	// Set the blending function
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	// // Enable face culling
	// glEnable( GL_CULL_FACE );
	// glCullFace( GL_BACK );

	// Enable the Z-Buffer
	glEnable( GL_DEPTH_TEST );

	// Set the type of drawing (Fill or Stroke)
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	// Initialise ImGUI

	// Create an ImGUI context and initialise it to this window
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup the colour style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL( m_window, true );
	ImGui_ImplOpenGL3_Init( "#version 460 core" );

	// Instantiate the camera
	Camera::Instantiate( glm::vec3( 0.0f, 5.0f, 0.0f ) );
}

void Window::CallbackResize( GLFWwindow* p_window, int dx, int dy )
{
	// Get the correct window then resize it
	void* ptr = glfwGetWindowUserPointer( p_window );
	if ( Window* winPtr = static_cast<Window*>( ptr ) )
		winPtr->Resize();
}

void Window::CallbackKeyboard( GLFWwindow* p_window, int key, int scancode, int action, int mods )
{
	// Escape Key
	if ( key == Key::ESC )
		if ( action == GLFW_PRESS )
			KeyboardHandler::Set( Key::ESC, true );
		else if ( action == GLFW_RELEASE )
			KeyboardHandler::Set( Key::ESC, false );

	// Left Shift
	if ( key == Key::L_SHIFT )
		if ( action == GLFW_PRESS )
			KeyboardHandler::Set( Key::L_SHIFT, true );
		else if ( action == GLFW_RELEASE )
			KeyboardHandler::Set( Key::L_SHIFT, false );

	// F1 Key
	if ( key == Key::F1 )
		if ( action == GLFW_PRESS )
			KeyboardHandler::Set( Key::F1, true );
		else if ( action == GLFW_RELEASE )
			KeyboardHandler::Set( Key::F1, false );

	// Camera movement

	// Forward
	if ( key == Key::W )
		if ( action == GLFW_PRESS )
			KeyboardHandler::Set( Key::W, true );
		else if ( action == GLFW_RELEASE )
			KeyboardHandler::Set( Key::W, false );

	// Left
	if ( key == Key::A )
		if ( action == GLFW_PRESS )
			KeyboardHandler::Set( Key::A, true );
		else if ( action == GLFW_RELEASE )
			KeyboardHandler::Set( Key::A, false );

	// Back
	if ( key == Key::S )
		if ( action == GLFW_PRESS )
			KeyboardHandler::Set( Key::S, true );
		else if ( action == GLFW_RELEASE )
			KeyboardHandler::Set( Key::S, false );

	// Right
	if ( key == Key::D )
		if ( action == GLFW_PRESS )
			KeyboardHandler::Set( Key::D, true );
		else if ( action == GLFW_RELEASE )
			KeyboardHandler::Set( Key::D, false );

	// Up
	if ( key == Key::SPACE )
		if ( action == GLFW_PRESS )
			KeyboardHandler::Set( Key::SPACE, true );
		else if ( action == GLFW_RELEASE )
			KeyboardHandler::Set( Key::SPACE, false );

	// Down
	if ( key == Key::L_CTRL )
		if ( action == GLFW_PRESS )
			KeyboardHandler::Set( Key::L_CTRL, true );
		else if ( action == GLFW_RELEASE )
			KeyboardHandler::Set( Key::L_CTRL, false );
}

void Window::CallbackMouse( GLFWwindow* p_window, double xPos, double yPos )
{
	if ( m_firstMouse )
	{
		m_prevMouseX = xPos;
		m_prevMouseY = yPos;
		m_firstMouse = false;
	}

	float xOff	 = xPos - m_prevMouseX;
	float yOff	 = m_prevMouseY - yPos; // Reverse because y-axis is from bottom to top
	m_prevMouseX = xPos;
	m_prevMouseY = yPos;

	Camera::ProcessMouse( xOff, yOff );
}

void Window::CallbackScroll( GLFWwindow* p_window, double xOff, double yOff )
{
	Camera::ProcessMouseScroll( (float)yOff );
}

void Window::Resize()
{
	// Resize the viewport after finding out what size the window is now
	glfwGetFramebufferSize( m_window, &m_size[0], &m_size[1] );
	glViewport( 0, 0, m_size[0], m_size[1] );
}

void Window::SetFullscreen( bool fullscreen )
{
	// If the window is already in the new state then return
	if ( ( glfwGetWindowMonitor( m_window ) != nullptr ) == fullscreen )
		return;

	if ( fullscreen )
	{
		// Backup the position and size
		glfwGetWindowPos( m_window, &m_pos[0], &m_pos[1] );
		glfwGetWindowSize( m_window, &m_size[0], &m_size[1] );

		// Get the resolution of the monitor
		const GLFWvidmode* mode = glfwGetVideoMode( m_monitor );

		// Switch to fullscreen
		glfwSetWindowMonitor( m_window, m_monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE );

		std::cout << "Window is now fullscreen" << std::endl;
	}
	else
	{
		// Restore the window size and position
		glfwSetWindowMonitor( m_window, nullptr, m_pos[0], m_pos[1], m_size[0], m_size[1], GLFW_DONT_CARE );

		std::cout << "Window is now not fullscreen" << std::endl;
	}

	// Change the size of the window
	Resize();
}

void Window::MainLoop()
{
	// Timing variables
	float currentTime = 0.0f, deltaTime = 0.0f, lastFrame = glfwGetTime();

	// Create the main scene
	Scene::MainScene mainScene( m_size[0], m_size[1] );

	while ( !glfwWindowShouldClose( m_window ) )
	{
		// Timing calculations
		currentTime = glfwGetTime();
		deltaTime	= currentTime - lastFrame;
		lastFrame	= currentTime;

		// Update and render scene
		mainScene.OnUpdate( deltaTime );
		mainScene.OnRender();

		// Call a new ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		mainScene.OnImGuiRender();

		// Render ImGui
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData( ImGui::GetDrawData() );

		// Process Inputs
		KeyboardHandler::ProcessInput( m_window, deltaTime );

		glfwPollEvents();			 // Check for and resolve events
		glfwSwapBuffers( m_window ); // Swap the front and back buffer
	}

	// Delete the ImGui context
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Terminate the OpenGL context and window
	glfwDestroyWindow( m_window );
	glfwTerminate();
}