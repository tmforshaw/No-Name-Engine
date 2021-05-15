#pragma once
#include "../Buffers/IndexBuffer.hpp"
#include "../Buffers/VertexArray.hpp"
#include "../Buffers/VertexBuffer.hpp"
#include "../Camera/Camera.hpp"
#include "../Shader/Shader.hpp"
#include "../Texture/Texture.hpp"
#include "Scene.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include <vector>

namespace Scene
{
	class MainScene : public Scene
	{
	private:
		std::unique_ptr<VertexArray>   m_VAO;
		std::unique_ptr<VertexBuffer>  m_vertexBuffer;
		std::unique_ptr<IndexBuffer>   m_indexBuffer;
		std::unique_ptr<ShaderProgram> m_shader;
		std::unique_ptr<Texture>	   m_texture;
		std::unique_ptr<Texture>	   m_textureAtlas;

		// Projections
		glm::mat4 m_proj;

	public:
		MainScene( const unsigned int& winWidth, const unsigned int& winHeight );
		~MainScene();

		void OnUpdate( const float& deltaTime ) override;
		void OnRender() override;
		void OnImGuiRender() override;
	};

} // namespace Scene