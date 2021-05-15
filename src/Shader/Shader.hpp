#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <unordered_map> // Caching locations

class ShaderProgram
{
private:
	const char*							 m_programPath;
	unsigned int						 m_rendererID;
	std::unordered_map<std::string, int> m_uniformLocationCache;

	bool ParseShader( const char*& path, std::string* vertexString, std::string* fragmentString ) const;
	bool CompileShader( const char* vertexString, const char* fragmentString );
	int	 GetUniformLocation( const char*& name );

public:
	ShaderProgram( const char* path );
	~ShaderProgram();

	void Bind() const;
	void UnBind() const;

	// Set uniform variables

	void SetUniform1i( const char* name, const int& v0 );
	void SetUniform1ui( const char* name, const unsigned int& v0 );

	void SetUniform1f( const char* name, const float& v0 );
	void SetUniform2f( const char* name, const float& v0, const float& v1 );
	void SetUniform3f( const char* name, const float& v0, const float& v1, const float& v2 );
	void SetUniform4f( const char* name, const float& v0, const float& v1, const float& v2, const float& v3 );

	void SetUniformMat4f( const char* name, glm::mat4 matrix );
};