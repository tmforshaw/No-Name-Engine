#pragma once
#include <fstream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <sstream>
#include <string>

class Shader
{
public:
	unsigned int ID;

	Shader( const char* vertexPath, const char* fragmentPath )
	{
		// 1. Get the vertex and fragment shader source code
		std::string	  vertexCode, fragmentCode;
		std::ifstream vShaderFile, fShaderFile;

		// Allow ifstream to throw exceptions
		vShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );
		fShaderFile.exceptions( std::ifstream::failbit | std::ifstream::badbit );

		try
		{
			// Open the files
			vShaderFile.open( vertexPath );
			fShaderFile.open( fragmentPath );
			std::stringstream vShaderStream, fShaderStream;

			// Read the file's buffer contents into the streams;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			// Close the file handlers
			vShaderFile.close();
			fShaderFile.close();

			// Convert stream into string
			vertexCode	 = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch ( std::ifstream::failure e )
		{
			std::cout << "ERROR::SHADER::FILE_UNABLE_TO_READ" << std::endl;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();

		// 2. Compile shaders
		unsigned int vertex, fragment;
		int			 success;
		char		 errorInfo[512];

		// Vertex shader
		vertex = glCreateShader( GL_VERTEX_SHADER );
		glShaderSource( vertex, 1, &vShaderCode, NULL );
		glCompileShader( vertex );

		// Check for a print errors
		glGetShaderiv( vertex, GL_COMPILE_STATUS, &success );
		if ( !success )
		{
			glGetShaderInfoLog( vertex, 512, NULL, errorInfo );
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_ERROR:\n"
					  << errorInfo << std::endl;
		}

		// Fragment shader
		fragment = glCreateShader( GL_FRAGMENT_SHADER );
		glShaderSource( fragment, 1, &fShaderCode, NULL );
		glCompileShader( fragment );

		// Check for a print errors
		glGetShaderiv( fragment, GL_COMPILE_STATUS, &success );
		if ( !success )
		{
			glGetShaderInfoLog( fragment, 512, NULL, errorInfo );
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_ERROR:\n"
					  << errorInfo << std::endl;
		}

		// Shader program
		ID = glCreateProgram();
		glAttachShader( ID, vertex );
		glAttachShader( ID, fragment );
		glLinkProgram( ID );

		// Print any linking errors
		glGetProgramiv( ID, GL_LINK_STATUS, &success );
		if ( !success )
		{
			glGetProgramInfoLog( ID, 512, NULL, errorInfo );
			std::cout << "ERROR::SHADER::PROGRAM::LINK_ERROR:\n"
					  << errorInfo << std::endl;
		}

		// Free the shader's memory
		glDeleteShader( vertex );
		glDeleteShader( fragment );
	}

	~Shader()
	{
		glDeleteProgram( ID );
	}

	void Use()
	{
		glUseProgram( ID );
	}

	// Utilities for uniforms
	void SetBool( const std::string& name, bool value ) const
	{
		glUniform1i( glGetUniformLocation( ID, name.c_str() ), (int)value );
	}

	void SetInt( const std::string& name, int value ) const
	{
		glUniform1i( glGetUniformLocation( ID, name.c_str() ), value );
	}

	// Floats

	void SetFloat( const std::string& name, float value ) const
	{
		glUniform1f( glGetUniformLocation( ID, name.c_str() ), value );
	}

	void SetFloat2( const std::string& name, float value1, float value2 )
	{
		glUniform2f( glGetUniformLocation( ID, name.c_str() ), value1, value2 );
	}

	void SetFloat3( const std::string& name, float value1, float value2, float value3 )
	{
		glUniform3f( glGetUniformLocation( ID, name.c_str() ), value1, value2, value3 );
	}

	void SetFloat4( const std::string& name, float value1, float value2, float value3, float value4 )
	{
		glUniform4f( glGetUniformLocation( ID, name.c_str() ), value1, value2, value3, value4 );
	}

	// Matrices

	void SetMat4( const std::string& name, glm::mat4 value ) const
	{
		glUniformMatrix4fv( glGetUniformLocation( ID, name.c_str() ), 1, GL_FALSE, glm::value_ptr( value ) );
	}
};