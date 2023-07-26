/* \file OpenGLShader.cpp*/

#include "engine_pch.h"
#include <glad/glad.h>
#include "platform/OpenGL/OpenGLShader.h"
#include "fstream"
#include "systems/log.h"
#include <string>
#include <array>
#include <glm/gtc/type_ptr.hpp>

namespace Engine
{
	OpenGlShader::OpenGlShader(const char* vertexfilepath, const char* fragmentfilepath)
	{
		std::string line, Vertexsrc, fragmentSrc;
		std::fstream handle(vertexfilepath, std::ios::in);
		if (handle.is_open())
		{
			

			while (getline(handle, line))
			{
				Vertexsrc += (line + "\n");
			}
		}
		else 
		{
			Log::error("Could not open shader source: {0} ", vertexfilepath);
			return;
		}
		handle.close();
		handle.open(fragmentfilepath, std::ios::in);
		if (handle.is_open())
		{


			while (getline(handle, line))
			{
				fragmentSrc += (line + "\n");
			}
		}
		else
		{
			Log::error("Could not open shader source: {0} ", vertexfilepath);
			return;
		}
		handle.close();
		compiledLinked(Vertexsrc.c_str(), fragmentSrc.c_str());
	}
	OpenGlShader::OpenGlShader(const char* filepath)
	{
		enum Region { None = -1, Vertex = 0, Fragment, Geometry, TessllationControl, TesselationEvaluation, Compute };
		std::string line;
		std::array < std::string, Region::Compute + 1 > src;
		uint32_t region = Region::None;

		std::fstream handle(filepath, std::ios::in);
		if (handle.is_open())
		{


			while (getline(handle, line))
			{
				if (line.find("#region Vertex") != std::string::npos) { region = Region::Vertex; continue; }
				if (line.find("#region Fragment") != std::string::npos){region = Region::Fragment;continue; }
				if (line.find("#region Geometry") != std::string::npos){region = Region::Geometry;continue; }
				if (line.find("#region TessellationControl") != std::string::npos){region = Region::TessllationControl;continue; }
				if (line.find("#region TessellationEvaluation") != std::string::npos){region = Region::TesselationEvaluation;continue; }
				if (line.find("#region Compute") != std::string::npos){region = Region::Compute;continue; }
				
				if (region != Region::None)src[region] += (line + "\n");
			}
		}
		else
		{
			Log::error("Could not open shader source: {0} ", filepath);
			return;
		}
		handle.close();
		compiledLinked(src[Region::Vertex].c_str(), src[Region::Fragment].c_str());
	}
	OpenGlShader::OpenGlShader()
	{
	}
	OpenGlShader::~OpenGlShader()
	{
		glDeleteProgram(m_OpenGL_ID);
	}
	void OpenGlShader::uploadInt(const char* name, int value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform1i(uniformLocation, value);
	}
	void OpenGlShader::uploadfloat(const char* name, float value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform1f(uniformLocation, value);
	}
	void OpenGlShader::uploadfloat2(const char* name, const glm::vec2& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform2f(uniformLocation, value.x, value.y);
	}
	void OpenGlShader::uploadfloat3(const char* name, const glm::vec3& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform3f(uniformLocation, value.x, value.y, value.z);
	}
	void OpenGlShader::uploadfloat4(const char * name, const glm::vec4& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
	}
	void OpenGlShader::uploadMat4(const char * name, const glm::mat4& value)
	{
		uint32_t uniformLocation = glGetUniformLocation(m_OpenGL_ID, name);
		glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(value));
		
	}
	void OpenGlShader::compiledLinked(const char* vertShaderSrc, const char* fragmentShaderSrc)
	{

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		const GLchar* source = vertShaderSrc;
		glShaderSource(vertexShader, 1, &source, 0);
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(vertexShader);
			return;
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		source = fragmentShaderSrc;
		glShaderSource(fragmentShader, 1, &source, 0);
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader compile error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			return;
		}

		m_OpenGL_ID = glCreateProgram();
		glAttachShader(m_OpenGL_ID, vertexShader);
		glAttachShader(m_OpenGL_ID, fragmentShader);
		glLinkProgram(m_OpenGL_ID);

		GLint isLinked = 0;
		glGetProgramiv(m_OpenGL_ID, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(m_OpenGL_ID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_OpenGL_ID, maxLength, &maxLength, &infoLog[0]);
			Log::error("Shader linking error: {0}", std::string(infoLog.begin(), infoLog.end()));

			glDeleteProgram(m_OpenGL_ID);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			return;
		}

		glDetachShader(m_OpenGL_ID, vertexShader);
		glDetachShader(m_OpenGL_ID, fragmentShader);

	}
}