/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "core/application.h"
#ifdef NG_PLATFORM_WINDOWS
#include "platform/windows/WinTimer.h"
#endif // NG_PLATFORM_WINDOWS
#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFWSystem/GLFWSystem.h"
#endif // NG_PLATFORM_WINDOWS
#include "platform/OpenGL/OpenGLVertexArray.h"



#include "platform/OpenGL/OpenGLShader.h"
#ifdef NG_PLATFORM_WINDOWS
#include "platform/OpenGL/OpenGLTexture.h"
#endif // NG_PLATFORM_WINDOWS
namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start system

		// Start log
		m_logSysem.reset(new Log); //!<Initilise log system
		m_logSysem->start();


#ifdef NG_PLATFORM_WINDOWS
		//start window system
		m_windowSystem.reset(new GLFWSystem); //!<rest the window system
#endif

		m_windowSystem->start(); //!< start window system


		//Reset the timer
#ifdef NG_PLATFORM_WINDOWS
		m_timer.reset(new WinTimer); //!<Initilise timer system
#else
		m_timer.reset(new ChronoTimer);
#endif
		m_timer->start();

		m_window.reset(Window::create());

		m_window->getEventHandler().setOnCloseCallback(std::bind(&Application::onClose, this, std::placeholders::_1));

		FPSEulerCameraProps camProps;
		camProps.aspectRation = (float)m_window->getWidth() / (float)m_window->getHeight();
		camProps.rotationSpeed = 16.0f;
		m_camera.reset(new cameraControllerEuler(camProps));

		InputPoller::setCurrentWindow(m_window->getNativeWindow());
		m_timer->reset();
		

		
	}

	bool Application::onClose(WindowCloseEvents& e)//!< binding tool use for handler
	{
		e.handle(true);
		m_running = false;
		return e.handled();
	}

	Application::~Application()
	{

		// Stop System

		// Stop Logger
		m_logSysem->stop();
		//!<Stop window system
		m_windowSystem->stop();
	}


	void Application::run()
	{
#pragma region RAW_DATA

		float cubeVertices[8 * 24] = {
			//	 <------ Pos ------>  <--- normal --->  <-- UV -->
				 0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.f,   0.f,
				 0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.f,   0.5f,
				-0.5f, -0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.5f,
				-0.5f,  0.5f, -0.5f,  0.f,  0.f, -1.f,  0.33f, 0.f,

				-0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33f, 0.5f,
				 0.5f, -0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.5f,
				 0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.66f, 0.f,
				-0.5f,  0.5f, 0.5f,   0.f,  0.f,  1.f,  0.33,  0.f,

				-0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  1.f,   0.f,
				 0.5f, -0.5f, -0.5f,  0.f, -1.f,  0.f,  0.66f, 0.f,
				 0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  0.66f, 0.5f,
				-0.5f, -0.5f, 0.5f,   0.f, -1.f,  0.f,  1.0f,  0.5f,

				 0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.f,   0.5f,
				 0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.f,   1.0f,
				-0.5f,  0.5f, -0.5f,  0.f,  1.f,  0.f,  0.33f, 1.0f,
				-0.5f,  0.5f, 0.5f,   0.f,  1.f,  0.f,  0.3f,  0.5f,

				-0.5f,  0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 0.5f,
				-0.5f,  0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 0.5f,
				-0.5f, -0.5f, -0.5f, -1.f,  0.f,  0.f,  0.33f, 1.0f,
				-0.5f, -0.5f, 0.5f,  -1.f,  0.f,  0.f,  0.66f, 1.0f,

				 0.5f, -0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  1.0f,
				 0.5f,  0.5f, -0.5f,  1.f,  0.f,  0.f,  1.0f,  0.5f,
				 0.5f,  0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 0.5f,
				 0.5f, -0.5f, 0.5f,   1.f,  0.f,  0.f,  0.66f, 1.0f
		};

		float pyramidVertices[6 * 16] = {
			//	 <------ Pos ------>  <--- colour ---> 
				-0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f, //  square Magneta
				 0.5f, -0.5f, -0.5f,  0.8f, 0.2f, 0.8f,
				 0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,
				-0.5f, -0.5f,  0.5f,  0.8f, 0.2f, 0.8f,

				-0.5f, -0.5f, -0.5f,  0.2f, 0.8f, 0.2f,  //triangle Green
				-0.5f, -0.5f,  0.5f,  0.2f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.2f, 0.8f, 0.2f,

				-0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f, //triangle Red
				 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.f,
				 0.0f,  0.5f,  0.0f,  1.0f, 0.0f, 0.f,

				 0.5f, -0.5f,  0.5f,  0.8f, 0.8f, 0.2f, //  triangle Yellow
				 0.5f, -0.5f, -0.5f,  0.8f, 0.8f, 0.2f,
				 0.0f,  0.5f,  0.0f,  0.8f, 0.8f, 0.2f,

				 0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,//  triangle Blue
				-0.5f, -0.5f, -0.5f,  0.f, 0.2f, 1.0f,
				 0.0f,  0.5f,  0.0f,  0.f, 0.2f, 1.0f
		};

		uint32_t pyramidIndices[3 * 6] =
		{
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			7, 8, 9,
			10, 11, 12,
			13, 14, 15
		};

		uint32_t cubeIndices[3 * 12] = {
			0, 1, 2,
			2, 3, 0,
			4, 5, 6,
			6, 7, 4,
			8, 9, 10,
			10, 11, 8,
			12, 13, 14,
			14, 15, 12,
			16, 17, 18,
			18, 19, 16,
			20, 21, 22,
			22, 23, 20
		};
#pragma endregion

#pragma region GL_BUFFERS
	
		std::shared_ptr <OpenGLVertexArray> cubeVAO;
		std::shared_ptr <OpenGLVertexBuffer> cubeVBO;
		std::shared_ptr <OpenGLIndexBuffer> cubeIBO;


		cubeVAO.reset(new OpenGLVertexArray);

		BufferLayout cubeBL = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 };
		cubeVBO.reset(new OpenGLVertexBuffer(cubeVertices, sizeof(cubeVertices), cubeBL));

		cubeIBO.reset(new OpenGLIndexBuffer(cubeIndices, 36));

		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->setIndexBuffer(cubeIBO);

		// Unbind everything so we can't mess is up
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		

		std::shared_ptr <OpenGLVertexArray> pyramidVAO;
		std::shared_ptr <OpenGLVertexBuffer> pyramidVBO;
		std::shared_ptr <OpenGLIndexBuffer> pyramidIBO;

		pyramidVAO.reset(new OpenGLVertexArray);
		BufferLayout pyramidBL = { ShaderDataType::Float3, ShaderDataType::Float3 };
		pyramidVBO.reset(new OpenGLVertexBuffer(pyramidVertices, sizeof(pyramidVertices), pyramidBL));

		pyramidIBO.reset(new OpenGLIndexBuffer(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);


		// Unbind everything so we can't mess is up
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#pragma endregion


#pragma region SHADERS
		std::shared_ptr<OpenGlShader> FCShader;
		FCShader.reset(new OpenGlShader("./assets/shaders/flatColour.glsl"));

		std::shared_ptr<OpenGlShader> TPShader;
		TPShader.reset(new OpenGlShader("./assets/shaders/texturedPhong.glsl"));

#pragma endregion 

#pragma region TEXTURES

		std::shared_ptr<OpenGLTexture> letterTexture;
		letterTexture.reset(new OpenGLTexture("./assets/textures/letterCube.png", 0));
		std::shared_ptr<OpenGLTexture> numberTexture;
		numberTexture.reset(new OpenGLTexture("./assets/textures/numberCube.png", 1));



#pragma endregion

		/*glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)*/
	//);
		//glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		float timestep = 0.f;

		while (m_running)
		{
			timestep = m_timer->getElapsedTime();
			m_timer->reset();
			
			// Do frame stuff
			for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(FCShader->getID());
			glBindVertexArray(pyramidVAO->getRenderID());

			FCShader->uploadMat4("u_model", models[0]);
			FCShader->uploadMat4("u_view", m_camera->getCamera().view);
			FCShader->uploadMat4("u_projection", m_camera->getCamera().projection);

			glDrawElements(GL_TRIANGLES, 3 * 6, GL_UNSIGNED_INT, nullptr);

			glUseProgram(TPShader->getID());
			glBindVertexArray(cubeVAO->getRenderID());
			
			lightColour = glm::vec3(1.f, 1.f, 1.f);
			lightPos = glm::vec3(1.f, 4.f, 6.f);
			viewPos = glm::vec3(0.f, 0.f, 0.f);

			TPShader->uploadMat4("u_model", models[1]);
			TPShader->uploadMat4("u_view", m_camera->getCamera().view);
			TPShader->uploadMat4("u_projection", m_camera->getCamera().projection);

			TPShader->uploadfloat3("u_lightColour", lightColour);
			TPShader->uploadfloat3("u_lightPos", lightPos);
			TPShader->uploadfloat3("u_viewPos", viewPos);
			TPShader->uploadInt("u_texData", 0);
			
			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);
			TPShader->uploadMat4("u_model", models[2]);
			TPShader->uploadInt("u_texData", 1);

			glDrawElements(GL_TRIANGLES, cubeVAO->getDrawCount(), GL_UNSIGNED_INT, nullptr);

			

			
			m_camera->onUpdate(timestep);
			m_window->onUpdate(timestep);
		};

	
	}

}
