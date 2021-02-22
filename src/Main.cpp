// clang-format off
#include <glad/glad.h> // GLAD must be before GLFW
#include <GLFW/glfw3.h>
// clang-format on

#include "Camera/Camera.hpp"
#include "Camera/Projections.hpp"
#include "Constants.hpp"
#include "Input/GL_Callbacks.hpp"
#include "Input/Input.hpp"
#include "Noise/PerlinNoise.hpp"
#include "ObjectBuffers/EntityBufferObject.hpp"
#include "ObjectBuffers/VertexArrayObject.hpp"
#include "ObjectBuffers/VertexBufferObject.hpp"
#include "Shaders/Shaders.hpp"
#include "Textures/Textures.hpp"
#include "World/World.hpp"

#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <random>

// Timing variables
float deltaT	= 0.0f; // Time between current frame and last frame
float lastFrame = 0.0f; // Time of last frame

int main()
{
	std::cout << "\nInitialising OpenGL\n\n";

	// Initialise GLFW
	glfwInit();

	// Configure GLFW
	glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );				 // OpenGL Version 3.x
	glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 3 );				 // OpenGL Version x.3
	glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE ); // Force to use modern OpenGL

	// Create a window (Specify primary monitor to enable fullscreen)
	GLFWwindow* window = glfwCreateWindow( width, height, "This is a test to see how long of a title I am allowed to put before something breaks, apparently I can just keep going and it works just fine ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", glfwGetPrimaryMonitor(), nullptr );
	if ( window == NULL )
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate(); // Close the window
		return -1;
	}

	// Set the window as the context
	glfwMakeContextCurrent( window );

	// Initialise GLAD so that OpenGL functions can be used

	// Load the address of the OpenGL function pointers (OS specific)
	if ( !gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	// Changing some OpenGL States

	// Set the size of the rendering window
	glViewport( 0, 0, width, height );

	// Hide the cursor and capture it into the window
	glfwSetInputMode( window, GLFW_CURSOR, GLFW_CURSOR_DISABLED );

	// Enable the use of the z-buffer
	glEnable( GL_DEPTH_TEST );

	// Enable face culling
	glEnable( GL_CULL_FACE );
	glCullFace( GL_BACK );

	// Register callback functions here

	glfwSetFramebufferSizeCallback( window, ResizeViewportCallback ); // Window resizing
	glfwSetKeyCallback( window, KeyboardCallback );
	glfwSetCursorPosCallback( window, MouseCallback ); // Monitor mouse
	glfwSetScrollCallback( window, ScrollCallback );   // Monitor Scrolling

	// Shaders

	// Query the max number of attributes that can be used for the vertex shader
	int attrAmt;
	glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &attrAmt );
	std::cout << "Max number of vertex attributes supported: " << attrAmt << std::endl;

	Shader shader( "./src/Shaders/VertexShader.GLSL", "./src/Shaders/FragmentShader.GLSL" );

	/// Create and establish the data of the VAO, EBO, and the VBO
	VertexArrayObject  VAO = VertexArrayObject();
	EntityBufferObject EBO = EntityBufferObject( sizeof( Cube::indices ), Cube::indices, GL_STATIC_DRAW );
	VertexBufferObject VBO = VertexBufferObject( sizeof( Cube::vertices ), Cube::vertices, GL_STATIC_DRAW );

	// Instantiate the texture
	Texture cubeTex( "src/Textures/Caveman.jpeg" );
	shader.Use();					// Apply the shader
	shader.SetInt( "texture1", 0 ); // Set the texture index in the shader

	// Set the type of drawing (Fill or Stroke)
	glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

	// Generate the chunk
	world.GenerateChunkMeshes( cam.GetPos() );

	// Draw Loop
	while ( !glfwWindowShouldClose( window ) )
	{
		// Check for and resolve user input
		kb.ProcessInput( window, deltaT );

		// Process time
		float currentFrame = glfwGetTime();			   // Time now
		deltaT			   = currentFrame - lastFrame; // Time since last frame
		lastFrame		   = currentFrame;

		// Clear the colour and depth buffers
		glClearColor( 0.2f, 0.3f, 0.3f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		// Bind and activate the textures
		cubeTex.Bind();

		// Move the camera and change the zoom
		view	   = cam.GetViewMatrix();
		projection = glm::perspective( glm::radians( cam.fov ), (float)width / (float)height, 0.1f, 100.0f );

		// Update the shader uniform values
		// shader.SetFloat3( "addedColour", sin( currentFrame ), cos( currentFrame ), sin( currentFrame * 0.75 ) );

		// Update the shader projection uniforms
		shader.SetMat4( "view", view );
		shader.SetMat4( "projection", projection );

		// Bind the correct VAO
		VAO.Bind();

		model = glm::translate( glm::mat4( 1.0f ), glm::vec3( 0.0f, 0.0f, 0.0f ) );
		shader.SetMat4( "model", model );

		world.DrawChunks( &VBO );

		// Check for and resolve triggered events
		glfwPollEvents();

		// Swap the front and back buffers (Show the buffer on the scren)
		glfwSwapBuffers( window );
	}

	// Deallocate all resources
	VAO.~VertexArrayObject();
	VBO.~VertexBufferObject();
	shader.~Shader();

	// Stop OpenGL
	glfwTerminate();
	return 0;
}