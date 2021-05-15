#include "MainScene.hpp"

#include "../../dependencies/imgui/imgui.h"
#include "../Buffers/BufferLayout.hpp"
#include "../Buffers/Vertex.hpp"
#include "../Renderer/Renderer.hpp"
#include "../World/Cube.hpp"
#include "../World/World.hpp"

// clang-format off
#include <glad/glad.h> // GLAD must be before GLFW
#include <GLFW/glfw3.h>
// clang-format on

namespace Scene
{
	MainScene::MainScene( const unsigned int& winWidth, const unsigned int& winHeight )
		: m_proj( glm::perspective( glm::radians( 50.0f ), (float)winWidth / (float)winHeight, 0.1f, 100.0f ) )
	{
		std::vector<Vertex>		  verticesVec = {};
		std::vector<unsigned int> indicesVec  = {};

		// m_VAO = std::make_unique<VertexArray>();

		World::Init();

		World::PushChunkVertices( &verticesVec, &indicesVec );

		// Create the buffers
		m_VAO		   = std::make_unique<VertexArray>();
		m_vertexBuffer = std::make_unique<VertexBuffer>( verticesVec.data(), verticesVec.size() * sizeof( Vertex ) );
		m_indexBuffer  = std::make_unique<IndexBuffer>( indicesVec.data(), indicesVec.size() );

		// for ( unsigned short i = verticesVec.size() - 100; i < verticesVec.size(); i++ )
		// {
		// 	std::cout << i << ":   ";

		// 	for ( unsigned short j = 0; j < 6; j++ )
		// 	{
		// 		if ( j < 3 )
		// 		{
		// 			std::cout << verticesVec[i].m_position[j] << ' ';

		// 			if ( j == 2 ) std::cout << ' ';
		// 		}
		// 		else if ( j < 5 )
		// 		{
		// 			std::cout << verticesVec[i].m_uvCoords[j - 3] << ' ';

		// 			if ( j == 4 ) std::cout << ' ';
		// 		}
		// 		else
		// 			std::cout << verticesVec[i].m_ID << "   ";
		// 	}

		// 	std::cout << std::endl;
		// }

		// for ( unsigned short i = indicesVec.size() / 6 - 100; i < indicesVec.size() / 6; i++ )
		// {
		// 	std::cout << i << ":   ";

		// 	for ( unsigned short j = 0; j < 6; j++ )
		// 	{
		// 		std::cout << indicesVec[i * 6 + j] << ' ';
		// 	}

		// 	std::cout << std::endl;
		// }

		// Set the layout of the vertex attriubutes
		{ // Inside of scope to delete layout
			BufferLayout layout;
			layout.Push<float>( 3 );		// Position
			layout.Push<float>( 2 );		// Texture coordinates
			layout.Push<unsigned int>( 1 ); // Texture index
			m_VAO->AddBuffer( *m_vertexBuffer, layout );
		}

		// Create the shader program
		m_shader = std::make_unique<ShaderProgram>( "resources/shaders/Shader1.GLSL" );
		m_shader->Bind();

		// Apply the projections to the shader
		m_shader->SetUniformMat4f( "u_proj", m_proj );

		m_shader->SetUniformMat4f( "u_model", glm::mat4( 1.0f ) );

		// Create and set the texture atlas
		m_textureAtlas = std::make_unique<Texture>( "resources/textures/TextureAtlas.png" );
		m_shader->SetUniform1i( "u_textureAtlas", 0 ); // Use the texture bound to slot 1

		// Set the uniform texture atlas variables
		m_shader->SetUniform1f( "u_atlasTexWidth", TEX_ATLAS_WIDTH );
		m_shader->SetUniform1f( "u_atlasTexHeight", TEX_ATLAS_HEIGHT );
		m_shader->SetUniform1ui( "u_atlasPixWidth", m_textureAtlas->GetWidth() );
	} // namespace Scene

	MainScene::~MainScene()
	{
	}

	void MainScene::OnUpdate( const float& deltaTime )
	{
		// m_shader->Bind();
		// m_shader->SetUniform4f( "u_colour", (float)sin( glfwGetTime() ), (float)cos( glfwGetTime() ), (float)sin( glfwGetTime() ), 1.0f );
	}

	void MainScene::OnRender()
	{
		Renderer::Clear();

		// Update the view matrix
		m_shader->Bind();
		m_shader->SetUniformMat4f( "u_view", Camera::GetViewMatrix() );

		// Render the chunks
		Renderer::Draw( *m_VAO, *m_indexBuffer, *m_shader );

		// World::DrawChunks( *m_VAO, *m_shader );
	}

	void MainScene::OnImGuiRender()
	{
	}
} // namespace Scene