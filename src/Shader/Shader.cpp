#include "Shader.hpp"

// clang-format off
#include <glad/glad.h> // GLAD must be before GLFW
#include <GLFW/glfw3.h>
// clang-format on

#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

enum class ShaderType
{
	NONE	 = -1,
	VERTEX	 = 0,
	FRAGMENT = 1
};

bool ShaderProgram::ParseShader( const char*& path, std::string* vertexString, std::string* fragmentString ) const
{
	std::ifstream fs;
	std::string	  line;

	// Open the file
	fs.open( path );

	if ( fs.is_open() )
	{
		std::stringstream ss[2];

		ShaderType type = ShaderType::NONE;

		while ( std::getline( fs, line ) ) // Hasn't reached the end of the file
		{
			if ( line.find( "#shader" ) != std::string::npos ) // Has a shader declaration
			{
				if ( line.find( "vertex" ) != std::string::npos ) // If it is declaring a vertex shader
					type = ShaderType::VERTEX;
				else if ( line.find( "fragment" ) != std::string::npos ) // If it is declaring a fragment shader
					type = ShaderType::FRAGMENT;
			}
			else
			{
				// Add to the correct string stream
				ss[(int)type] << line << '\n';
			}
		}

		// Set the string variables
		*vertexString	= ss[(int)ShaderType::VERTEX].str();
		*fragmentString = ss[(int)ShaderType::FRAGMENT].str();

		// Close the filestream
		fs.close();
	}
	else
	{
		std::cout << "ERROR::SHADER_PROGRAM::FILE_NOT_FOUND " << path << std::endl;

		return false;
	}

	return true;
}

bool ShaderProgram::CompileShader( const char* vertexString, const char* fragmentString )
{
	unsigned int vertex, fragment;

	// Error checking
	int	 success;
	char errorInfo[512];

	// Vertex shader
	vertex = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertex, 1, &vertexString, NULL );
	glCompileShader( vertex );

	// Check for a print errors
	glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
	if ( !success )
	{
		glGetShaderInfoLog( vertex, 512, NULL, errorInfo );
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_ERROR:\n"
				  << errorInfo << std::endl;

		return false;
	}

	// Fragment shader
	fragment = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragment, 1, &fragmentString, NULL );
	glCompileShader( fragment );

	// Check for a print errors
	glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
	if ( !success )
	{
		glGetShaderInfoLog( fragment, 512, NULL, errorInfo );
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_ERROR:\n"
				  << errorInfo << std::endl;

		return false;
	}

	// Shader program
	m_rendererID = glCreateProgram();
	glAttachShader( m_rendererID, vertex );
	glAttachShader( m_rendererID, fragment );
	glLinkProgram( m_rendererID );

	// Print any linking errors
	glGetProgramiv( m_rendererID, GL_LINK_STATUS, &success );
	if ( !success )
	{
		glGetProgramInfoLog( m_rendererID, 512, NULL, errorInfo );
		std::cout << "ERROR::SHADER::PROGRAM::LINK_ERROR:\n"
				  << errorInfo << std::endl;

		return false;
	}

	// Free the shader's memory
	glDeleteShader( vertex );
	glDeleteShader( fragment );

	std::cout << "Shader compiled successfully" << std::endl;

	return true;
}

int ShaderProgram::GetUniformLocation( const char*& name )
{
	if ( m_uniformLocationCache.find( name ) != m_uniformLocationCache.end() ) // If it's in the cache
		return m_uniformLocationCache[name];

	int location = glGetUniformLocation( m_rendererID, name );

	if ( location == -1 )
		std::cout << "WARNING::UNIFORM: '" << name << "' not found" << std::endl;

	m_uniformLocationCache[name] = location; // Cache it

	return location;
}

ShaderProgram::ShaderProgram( const char* path )
	: m_programPath( path ), m_rendererID( 0 )
{
	std::string vertexString, fragmentString;

	if ( ParseShader( path, &vertexString, &fragmentString ) ) // Compile the shader if it was parsed
		CompileShader( vertexString.c_str(), fragmentString.c_str() );
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram( m_rendererID );
}

void ShaderProgram::Bind() const
{
	glUseProgram( m_rendererID );
}

void ShaderProgram::UnBind() const
{
	glUseProgram( 0 );
}

// Set uniform variables

void ShaderProgram::SetUniform1i( const char* name, const int& v0 )
{
	glUniform1i( GetUniformLocation( name ), v0 );
}

void ShaderProgram::SetUniform1ui( const char* name, const unsigned int& v0 )
{
	glUniform1ui( GetUniformLocation( name ), v0 );
}

void ShaderProgram::SetUniform1f( const char* name, const float& v0 )
{
	glUniform1f( GetUniformLocation( name ), v0 );
}

void ShaderProgram::SetUniform2f( const char* name, const float& v0, const float& v1 )
{
	glUniform2f( GetUniformLocation( name ), v0, v1 );
}

void ShaderProgram::SetUniform3f( const char* name, const float& v0, const float& v1, const float& v2 )
{
	glUniform3f( GetUniformLocation( name ), v0, v1, v2 );
}

void ShaderProgram::SetUniform4f( const char* name, const float& v0, const float& v1, const float& v2, const float& v3 )
{
	glUniform4f( GetUniformLocation( name ), v0, v1, v2, v3 );
}

void ShaderProgram::SetUniformMat4f( const char* name, glm::mat4 matrix )
{
	glUniformMatrix4fv( GetUniformLocation( name ), 1, GL_FALSE, &matrix[0][0] );
}
