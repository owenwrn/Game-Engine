/** \file application.cpp
*/

#include "engine_pch.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <filesystem>
#include "core/application.h"


#ifdef NG_PLATFORM_WINDOWS
#include "platform/windows/winTimer.h"
#include "platform/GLFW/GLFWWindowImp.h"
#endif

#ifdef NG_PLATFORM_WINDOWS
#include "platform/GLFW/GLFWSystem.h"
#endif

#include "platform/OpenGL//vertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "rendering/Renderer3D.h"
#include "rendering/Renderer2D.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"
#include "cameras/FixedOrthoController.h"
#include "cameras/FreeEulerController.h"
#include "cameras/FollowController.h"


namespace Engine {
	// Set static vars
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}

		// Start systems

		// Start log
		m_logSystem.reset(new Log);
		m_logSystem->start();

		//Start the windows System
#ifdef NG_PLATFORM_WINDOWS
		m_windowsSystem.reset(new GLFWSystem);
#endif
		m_windowsSystem->start();


		// reset timer
#ifdef NG_PLATFORM_WINDOWS
		m_timer.reset(new WinTimer);
#else
		m_timer.reset(new ChronoTimer);
#endif
		m_timer->start();

		WindowProperties props("My Game Engine", 1024, 800);
		m_window.reset(WindowBase::create(props));

		// Set up callbacks
		m_window->getEventHandler().setOnWinClose(std::bind(&Application::onClose, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWinResize(std::bind(&Application::onResize, this, std::placeholders::_1));
		m_window->getEventHandler().setOnWinMoved(std::bind(&Application::onMove, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyPressed(std::bind(&Application::onKeyPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnKeyReleased(std::bind(&Application::onKeyReleased, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseButtonPressed(std::bind(&Application::onMouseButtonPressed, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseButtonReleased(std::bind(&Application::onMouseButtonReleased, this, std::placeholders::_1));
		m_window->getEventHandler().setOnMouseMoved(std::bind(&Application::onMouseMove, this, std::placeholders::_1));

		// Set input poller
		InputPoller::setNativeWindow(m_window->getNativeWindow());
		
	}

	void Application::onClose(WindowCloseEvent& e)
	{
		Log::info("Shutting down");
		m_running = false;
	}

	bool Application::onResize(WindowResizeEvent& e)
	{
		e.handle(true);
		//Log::info("Window Resize event: ({0}, {1})", e.getWidth(), e.getHeight());
		return e.handled();;
	}

	bool Application::onMove(WindowMovedEvent& e)
	{
		e.handle(true);
		//Log::info("Window Move event: ({0}, {1})", e.getX(), e.getY());
		return e.handled();;
	}

	bool Application::onKeyPressed(KeyPressedEvent& e)
	{
		e.handle(true);
		//Log::info("Key pressed event: key: {0}, repeat: {1}", e.getKeyCode(), e.getRepeatCount());
		return e.handled();;
	}

	bool Application::onKeyReleased(KeyReleasedEvent& e)
	{
		e.handle(true);
		//Log::info("Key released event: key: {0}", e.getKeyCode());
		return e.handled();;
	}

	bool Application::onMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		e.handle(true);
		//Log::info("Mouse button pressed event: key: {0}", e.getCode());
		return e.handled();;
	}

	bool Application::onMouseButtonReleased(MouseButtonReleasedEvent& e)
	{
		e.handle(true);
		//Log::info("Mouse button released event: key: {0}", e.getCode());
		return e.handled();;
	}

	bool Application::onMouseMove(MouseMovedEvent& e)
	{
		e.handle(true);
		//Log::info("Mouse Move event: ({0}, {1})", e.getX(), e.getY());
		return e.handled();;
	}



	Application::~Application()
	{

		// Stop systems

		// Stop log
		m_logSystem->stop();
		// Stop windows system
		m_windowsSystem->stop();
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

		float pyramidVertices[8 * 16] = {
			//	 <------ Pos ------>  <--- normal --->	<---UV--->
				-0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,	0.f, 0.f,//  square Magneta
				 0.5f, -0.5f, -0.5f,  0.f, -1.f, 0.f,	0.f, 0.5f,
				 0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,	0.33f, 0.5f,
				-0.5f, -0.5f,  0.5f,  0.f, -1.f, 0.f,	0.33f, 0.f,

				-0.5f, -0.5f, -0.5f,  -0.8944f, 0.4472f, 0.0f,	0.33f, 0.f,  //triangle Green
				-0.5f, -0.5f,  0.5f,  -0.8944f, 0.4472f, 0.0f,	0.66f, 0.25f,
				 0.0f,  0.5f,  0.0f,  -0.8944f, 0.4472f, 0.0f,	0.33f, 0.5f,

				-0.5f, -0.5f,  0.5f,  0.0f, 0.4472f,0.8944f,	0.f, 0.f, //triangle Red
				 0.5f, -0.5f,  0.5f,  0.0f, 0.4472f,0.8944f,	0.f, 0.f,
				 0.0f,  0.5f,  0.0f,  0.0f, 0.4472f,0.8944f,	0.f, 0.f,

				 0.5f, -0.5f,  0.5f,  0.8944f, 0.4472f, 0.0f,	0.f, 0.f, //  triangle Yellow
				 0.5f, -0.5f, -0.5f,  0.8944f, 0.4472f, 0.0f,	0.f, 0.f,
				 0.0f,  0.5f,  0.0f,  0.8944f, 0.4472f, 0.0f,	0.f, 0.f,

				 0.5f, -0.5f, -0.5f,  0.0f, 0.4472f, -0.8944f,	0.f, 0.f,//  triangle Blue
				-0.5f, -0.5f, -0.5f,  0.0f, 0.4472f, -0.8944f,	0.f, 0.f,
				 0.0f,  0.5f,  0.0f,  0.0f, 0.4472f, -0.8944f,	0.f, 0.f,
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

		std::shared_ptr<VertexArray> cubeVAO;
		std::shared_ptr<VertexBuffer> cubeVBO;
		std::shared_ptr<IndexBuffer> cubeIBO;

		cubeVAO.reset(new VertexArray());

		VertexBufferLayout cubeBL = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 };
		cubeVBO.reset(new VertexBuffer(cubeVertices, sizeof(cubeVertices), cubeBL));

		cubeIBO.reset(new IndexBuffer(cubeIndices, 36));

		cubeVAO->addVertexBuffer(cubeVBO);
		cubeVAO->setIndexBuffer(cubeIBO);

		// Unbind everything so we can't mess is up
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		std::shared_ptr<VertexArray> pyramidVAO;
		std::shared_ptr<VertexBuffer> pyramidVBO;
		std::shared_ptr<IndexBuffer> pyramidIBO;

		pyramidVAO.reset(new VertexArray());
		VertexBufferLayout pyramidBL = { ShaderDataType::Float3, ShaderDataType::Float3, ShaderDataType::Float2 };
		pyramidVBO.reset(new VertexBuffer(pyramidVertices, sizeof(pyramidVertices), pyramidBL));

		pyramidIBO.reset(new IndexBuffer(pyramidIndices, 18));

		pyramidVAO->addVertexBuffer(pyramidVBO);
		pyramidVAO->setIndexBuffer(pyramidIBO);

		// Unbind everything so we can't mess is up
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

#pragma endregion

#pragma region SHADERS

		std::shared_ptr<OpenGLShader> FCShader;
		FCShader.reset(new OpenGLShader("./assets/shaders/flatColour.glsl"));

		std::shared_ptr<OpenGLShader> TPShader;
		TPShader.reset(new OpenGLShader("./assets/shaders/texturedPhong.glsl"));

		//std::shared_ptr<OpenGLShader> FCShader;
		//FCShader.reset(new OpenGLShader("./assets/shaders/flatColour.vert", "./assets/shaders/flatColour.frag"));

		//std::shared_ptr<OpenGLShader> TPShader;
		//TPShader.reset(new OpenGLShader("./assets/shaders/texturedPhong.vert", "./assets/shaders/texturedPhong.frag"));

#pragma endregion 

#pragma region TEXTURES

		std::shared_ptr<OpenGLTexture> letterTexture;
		letterTexture.reset(new OpenGLTexture("assets/textures/letterCube.png"));
		std::shared_ptr<OpenGLTexture> numberTexture;
		numberTexture.reset(new OpenGLTexture("assets/textures/numberCube.png"));

		std::shared_ptr<OpenGLTexture> moonTexture;
		moonTexture.reset(new OpenGLTexture("assets/textures/moon.png"));

		SubTexture letterSubTexture(letterTexture, { 0.f, 0.f }, { 1.0f, 0.5f });
		SubTexture numberSubTexture(numberTexture, { 0.f, 0.5f }, { 1.0f, 1.0f });
		//SubTexture moonSubTexture(moonTexture, { 0.5f, 0.0f }, { 1.0f, 1.0f });

		/*letterTexture->bindToSlot(0);
		numberTexture->bindToSlot(1);
		moonTexture->bindToSlot(2);*/

#pragma endregion

#pragma region MATERIALS

		Material pyramidMat(TPShader, glm::vec4(0.f, 0.5f, 1.f, 1.f));
		Material cubeMat(TPShader, letterTexture);
		Material cube2Mat(TPShader, numberTexture);


#pragma endregion

		glm::vec3 pos(-2.0f, 0.f, -6.f);
		float rot = 0.f;
		glm::mat4 models[3];
		models[0] = glm::translate(glm::mat4(1.0f), glm::vec3(-2.f, 0.f, -6.f));
		models[1] = glm::translate(glm::mat4(1.0f), glm::vec3(0.f, 0.f, -6.f));
		models[2] = glm::translate(glm::mat4(1.0f), glm::vec3(2.f, 0.f, -6.f));

		glm::mat4 view = glm::lookAt(
			glm::vec3(0.f, 0.f, 0.f),
			glm::vec3(0.f, 0.f, -1.f),
			glm::vec3(0.f, 1.f, 0.f)
		);
		glm::mat4 projection = glm::perspective(glm::radians(45.f), 1024.f / 800.f, 0.1f, 100.f);

#pragma region CAMERAS

		FixedOrthoParams orthoParams;
		orthoParams.position = glm::vec3(0.f);
		orthoParams._near = -10.f;
		orthoParams._far = 10.f;
		orthoParams.top = m_window->getHeight() / 2;
		orthoParams.bottom = -orthoParams.top;
		orthoParams.right = m_window->getWidth() / 2;
		orthoParams.left = -orthoParams.right;

		std::shared_ptr<FixedOthroController> orthoCam;
		orthoCam.reset(new FixedOthroController(orthoParams));

		FollowParams followParams;
		followParams.entityTransform = &models[0];
		followParams.offset = glm::vec3(0.f, 1.f, 4.f);
		followParams.aspectRatio = 4.f / 3.f;
		followParams.farClip = 100.f;
		followParams.nearClip = 0.1f;
		followParams.fovY = 45.f;


		std::shared_ptr<FollowController> followCam;
		followCam.reset(new FollowController(followParams));

		FreeEulerParams eulerParams;
		eulerParams.aspectRatio = 4.f / 3.f;
		eulerParams.farClip = 100.f;
		eulerParams.nearClip = 0.1f;
		eulerParams.fovY = 45.f;
		eulerParams.sensitivity = 1000.f;
		eulerParams.speed = 5.f;
		eulerParams.ScrHeight = m_window->getHeight();
		eulerParams.ScrWidth = m_window->getWidth();

		std::shared_ptr<FreeEulerController> eulerCam;
		eulerCam.reset(new FreeEulerController(eulerParams));

		m_camera = eulerCam;

#pragma endregion

		//// Camera UBO
		uint32_t blockNumber = 0;
		//uint32_t cameraUBO;
		//UniformBufferLayout camLayout = { {"u_projection", ShaderDataType::Mat4},  {"u_view", ShaderDataType::Mat4} };

		//glGenBuffers(1, &cameraUBO);
		//glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO);
		//glBufferData(GL_UNIFORM_BUFFER, camLayout.getStride(), nullptr, GL_DYNAMIC_DRAW);
		//glBindBufferRange(GL_UNIFORM_BUFFER, blockNumber, cameraUBO, 0, camLayout.getStride());
		//
		//uint32_t blockIndex = glGetUniformBlockIndex(FCShader->getID(), "b_camera");
		//glUniformBlockBinding(FCShader->getID(), blockIndex, blockNumber);

		//blockIndex = glGetUniformBlockIndex(TPShader->getID(), "b_camera");
		//glUniformBlockBinding(TPShader->getID(), blockIndex, blockNumber);

		//auto& element = *camLayout.begin();
		//glBufferSubData(GL_UNIFORM_BUFFER, element.m_offset, element.m_size, glm::value_ptr(projection));
		//element = *(camLayout.begin() +1);
		//glBufferSubData(GL_UNIFORM_BUFFER, element.m_offset, element.m_size, glm::value_ptr(view));

		UniformBufferLayout camLayout = { {"u_projection", ShaderDataType::Mat4},  {"u_view", ShaderDataType::Mat4} };

		std::shared_ptr<OpenGLUniformBuffer> cameraUBO;
		cameraUBO.reset(new OpenGLUniformBuffer(camLayout));

		cameraUBO->attachShaderBlock(FCShader, "b_camera");
		cameraUBO->attachShaderBlock(TPShader, "b_camera");

		cameraUBO->uploadData("u_projection", glm::value_ptr(m_camera->getCamera().projection));
		cameraUBO->uploadData("u_view", glm::value_ptr(m_camera->getCamera().view));

		blockNumber++;
		glm::vec3 lightColour(1.f, 1.f, 1.f);
		glm::vec3 lightPos(1.f, 4.f, 6.f);
		glm::vec3 viewPos(0.f, 0.f, 0.f);

		/*
		uint32_t lightDataSize = sizeof(glm::vec4) * 3;
		

		glGenBuffers(1, &lightsUBO);
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
		glBufferData(GL_UNIFORM_BUFFER, lightDataSize, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, blockNumber, lightsUBO, 0, lightDataSize);

		uint32_t blockIndex = glGetUniformBlockIndex(TPShader->getID(), "b_lights");
		glUniformBlockBinding(TPShader->getID(), blockIndex, blockNumber);

		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::vec3), glm::value_ptr(lightPos));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4), sizeof(glm::vec3), glm::value_ptr(viewPos));
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::vec4) * 2, sizeof(glm::vec3), glm::value_ptr(lightColour));*/

		UniformBufferLayout lightsLayout = { {"u_lightColour", ShaderDataType::Float4}, {"u_lightColour", ShaderDataType::Float4}, {"u_lightColour", ShaderDataType::Float4} };

		std::shared_ptr<OpenGLUniformBuffer> lightsUBO;
		lightsUBO.reset(new OpenGLUniformBuffer(lightsLayout));

		lightsUBO->attachShaderBlock(TPShader, "b_lights");

		
		lightsUBO->uploadData("u_lightPos", glm::value_ptr(lightPos));
		lightsUBO->uploadData("u_viewPos", glm::value_ptr(viewPos));
		lightsUBO->uploadData("u_lightColour", glm::value_ptr(lightColour));

		glm::mat4 view2D = glm::mat4(1.f);
		glm::mat4 projection2D = glm::ortho(0.f, static_cast<float>(m_window->getWidth()), static_cast<float>(m_window->getHeight()), 0.f);

		SceneWideUniforms swu3D;
		/*swu3D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_camera->getCamera().projection)));
		swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_camera->getCamera().view)));*/

		SceneWideUniforms swuOrtho;
		swu3D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_camera->getCamera().projection)));
		swu3D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(m_camera->getCamera().view)));

		SceneWideUniforms swu2D;
		swu2D["u_view"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(view2D)));
		swu2D["u_projection"] = std::pair<ShaderDataType, void*>(ShaderDataType::Mat4, static_cast<void*>(glm::value_ptr(projection2D)));

		Quad quads[6] =
		{
			Quad::createCentreHalf({300.f, 200.f}, {100.f, 50.f}),
			Quad::createCentreHalf({200.f, 200.f}, {50.f, 50.f}),
			Quad::createCentreHalf({400.f, 500.f}, {75.f, 75.f}),
			Quad::createCentreHalf({100.f, 200.f}, {75.f, 50.f}),
			Quad::createCentreHalf({100.f, 500.f}, {50.f, 25.f}),
			Quad::createCentreHalf({300.f, 50.f}, {75.f, 100.f}),
		};

		glEnable(GL_DEPTH_TEST);
		glClearColor(0.26f, 0.98f, 0.80f, 1.0f);

		float timestep = 0.1f;

		Renderer3D::init();
		Renderer2D::init();

		while (m_running)
		{
			timestep = m_timer->getTimeElapsed();
			m_timer->reset();
			//Log::trace("FPS {0}", 1.0f / timestep);

			if (InputPoller::isKeyPressed(NG_KEY_T)) { m_camera = followCam; }

			models[0] = glm::translate(glm::mat4(1.0f), pos) * glm::rotate(glm::mat4(1.0f), rot, glm::vec3(0.f, 1.0f, 0.f));

			if (InputPoller::isKeyPressed(NG_KEY_J)) { pos.x -= timestep, 0.f, 0.f; }
			if (InputPoller::isKeyPressed(NG_KEY_L)) { pos.x += timestep, 0.f, 0.f; }
			if (InputPoller::isKeyPressed(NG_KEY_I)) { pos.z += timestep, 0.f, 0.f; }
			if (InputPoller::isKeyPressed(NG_KEY_K)) { pos.z -= timestep, 0.f, 0.f; }
			if (InputPoller::isKeyPressed(NG_KEY_M)) { pos.y -= timestep, 0.f, 0.f; }
			if (InputPoller::isKeyPressed(NG_KEY_N)) { pos.y += timestep, 0.f, 0.f; }
			
			if (InputPoller::isKeyPressed(NG_KEY_U)) { rot += timestep; }
			if (InputPoller::isKeyPressed(NG_KEY_O)) { rot -= timestep; }

			//for (auto& model : models) { model = glm::rotate(model, timestep, glm::vec3(0.f, 1.0, 0.f)); }
			models[1] = glm::rotate(models[1], timestep, glm::vec3(0.f, 1.0f, 0.f));
			models[2] = glm::rotate(models[2], timestep, glm::vec3(0.f, 1.0f, 0.f));

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glEnable(GL_DEPTH_TEST);

			
			Renderer3D::begin(swu3D);

			Renderer3D::submit(pyramidVAO, pyramidMat, models[0]);
			Renderer3D::submit(cubeVAO, cubeMat, models[1]);
			Renderer3D::submit(cubeVAO, cube2Mat, models[2]);

			Renderer3D::end();

			glDisable(GL_DEPTH_TEST);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			Renderer2D::begin(swu2D);

			Renderer2D::submit(quads[0], {0.f, 0.5f, 1.f, 1.f});
			Renderer2D::submit(quads[1], letterSubTexture);
			Renderer2D::submit(quads[2], numberSubTexture ,{0.8f, 0.5f, .2f, 1.f});
			Renderer2D::submit(quads[3], numberSubTexture ,{1.f, 0.5f, 1.f, 1.f}, 45.f, true);
			Renderer2D::submit(quads[3], numberSubTexture ,{1.f, 0.5f, 1.f, 1.f}, glm::radians(-45.f));
			Renderer2D::submit(quads[4], numberSubTexture, 45.f, true);
			Renderer2D::submit(quads[5], { 1.f, 0.5f, 0.f, 0.5f }, glm::radians(-45.f));
			Renderer2D::submit(quads[5], { 0.f, 0.5f, 1.f, 0.5f }, 45.f, true);

			Renderer2D::end();

			glDisable(GL_BLEND);

			glBindBuffer(GL_UNIFORM_BUFFER, cameraUBO->getRenderID());
			cameraUBO->uploadData("u_projection", glm::value_ptr(m_camera->getCamera().projection));
			cameraUBO->uploadData("u_view", glm::value_ptr(m_camera->getCamera().view));

			m_camera->onUpdate(timestep);
			m_window->onUpdate(timestep);
		
		}

	}

}
