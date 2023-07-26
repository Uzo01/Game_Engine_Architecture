/* \file OpenGlShader.h*/
#pragma once

#include <cstdint>
#include <glm/glm.hpp>


namespace Engine
{
	class OpenGlShader
	{
	public:
		OpenGlShader(const char* vertexfilepath, const char* fragmentfilepath);
		OpenGlShader(const char* filepath);
		OpenGlShader();
		~OpenGlShader();
		uint32_t getID() const { return m_OpenGL_ID; }
		
		void uploadInt(const char* name, int value);
		void uploadfloat(const char* name, float value);
		void uploadfloat2(const char* name, const glm::vec2& value);//!<
		void uploadfloat3(const char* name, const glm::vec3& value);//!<
		void uploadfloat4(const char * name, const glm::vec4& value);//!<
		void uploadMat4(const char * name, const glm::mat4& value);//!<

	private:
		uint32_t m_OpenGL_ID;//!<
		void compiledLinked(const char* vertShaderSrc, const char* fragmentShaderSrc);//!<
	};
}