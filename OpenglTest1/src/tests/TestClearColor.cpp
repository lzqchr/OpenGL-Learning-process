#include"TestClearColor.h"
#include<GL/glew.h>
#include"Render.h"
#include"imgui/imgui.h"
#include"ComputeShader.h"

#include"Random.h"

#define N 512


namespace test {



	TestClearColor::TestClearColor(Camera& camera)
		:m_ClearColor{ 0.0f,1.0f,0.0f,1.0f }, m_Camera(camera)
	{
		float vertices0[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
		};

		float quadVertices[] = { 
		// positions   // texCoords
		-32.0f,	0.0f, -32.0f,  0.0f, 0.0f,
		 32.0f,	0.0f, -32.0f,  1.0f, 0.0f,
		-32.0f,	0.0f,  32.0f,  0.0f, 1.0f,
		 32.0f, 0.0f,  32.0f,  1.0f, 1.0f
		};

		float textVertices[] = { 
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
		};

		float uv[] = {
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f

		};

		float skyboxVertices[] = {
			// positions          
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};


		int bits = log2(512);

		// 创建一个数组来存储结果
		int in[512];

		// 遍历0到N的数字
		for (int i = 0; i < 512; i++) {
			// 创建一个数组来存储二进制数
			int binaryNum[512];

			// 调用函数将十进制数转换为二进制数
			decToBinary(i, binaryNum, bits);

			// 调用函数将二进制数反转并转换回十进制数
			in[i] = reverseBinary(binaryNum, bits);
		}
		
		for (int i = 0; i < 512; i++)
		{
			for (int j = 0; j < 512; j++)
			{
			
				gass.push_back(Random::Gauss());
				gass.push_back(Random::Gauss());
				gass.push_back(Random::Gauss());
				gass.push_back(Random::Gauss());
			}
		}
		float spacing = 10;
		float sX = -(N - 1) * spacing / 2.0;
		float sZ = (N - 1) * spacing / 2.0;
		float vX = 0.0;
		float vY = 0.0;

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				vertices.push_back ( sX);
				vertices.push_back (0.0);
				vertices.push_back (sZ);

				vertices.push_back  (vX);
				vertices.push_back  (vY);

				sX += spacing;

				vX += 1.0 / (N - 1);
			}
			sX = -(N - 1) * spacing / 2.0;
			sZ -= spacing;

			vX = 0.0;
			vY += 1.0 / (N - 1);
		}
		

		  
		for (int i = 0; i < N - 1; i++)
		{
			for (int j = 0; j < N - 1; j++)
			{
				indices.push_back(i * N + j);
				indices.push_back(i * N + j + 1);
				indices.push_back((i + 1) * N + j);
				indices.push_back(i * N + j + 1);
				indices.push_back((i + 1) * N + j);
				indices.push_back((i + 1) * N + j + 1);
			}
		}
		
		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (N - 1)* (N - 1) * 6 * 4, indices.data(), GL_STATIC_DRAW);
		

		
		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_Vao = std::make_unique<VertexArray>();
		//m_Vbo = std::make_unique<VertexBuffer>(textVertices,4*6*sizeof(float));
		//m_Vbo = std::make_unique<VertexBuffer>(quadVertices, 5 * 4 * sizeof(float));
		m_Vbo = std::make_unique<VertexBuffer>(vertices.data(), 512*512*5 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);//3
		layout.Push<float>(2);
		m_Vao->AddBuffer(*m_Vbo, layout);


		t_Vao = std::make_unique<VertexArray>();
		t_Vbo = std::make_unique<VertexBuffer>(uv, 4*6 * sizeof(float));

		VertexBufferLayout layout_t;
		layout_t.Push<float>(2);
		layout_t.Push<float>(2);
		t_Vao->AddBuffer(*t_Vbo, layout_t);


		cubeMap = std::make_unique<CubeMap>(faces);
		//cubeMap = std::make_unique<CubeMap>("res/skybox/sky.hdr");
		cubeMap_Vao = std::make_unique<VertexArray>();
		cubeMap_Vbo = std::make_unique<VertexBuffer>(skyboxVertices, 3 * 6 * 6 * sizeof(float));
		VertexBufferLayout layout_cubemap;
		layout_cubemap.Push<float>(3);
		cubeMap_Vao->AddBuffer(*cubeMap_Vbo, layout_cubemap);
		





		//m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

		/*
		m_Shader = std::make_unique<Shader>("res/shaders/triangle.shader");
		m_Shader->Bind();
		m_Shader->SetUniform1i("texture1", 0);
		m_Shader->SetUniformMat4f("model",model);
		m_Proj = glm::perspective(glm::radians(m_Camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
		m_View = m_Camera.GetViewMat();

		m_Texture = std::make_unique<mTexture>("res/textures/box.png");
		*/

		//m_Shader = std::make_unique<Shader>("res/shaders/frame.shader",true);
		m_Shader = std::make_unique<Shader>("res/shaders/ocean.shader");
		t_Shader = std::make_unique<Shader>("res/shaders/a_text.shader");
		cubeMap_Shader = std::make_unique<Shader>("res/shaders/cubeMap.shader");
		
		h0k_k_Shader = std::make_unique<ComputeShader>("res/shaders/hk.glsl");
		gass_Shader = std::make_unique<ComputeShader>("res/shaders/gass.glsl");
		dxyz_Shader = std::make_unique<ComputeShader>("res/shaders/displacement.glsl");
		Butterfly_T_Shader = std::make_unique<ComputeShader>("res/shaders/butterfly_Texture.glsl");
		butterfly_Compute_Shader = std::make_unique<ComputeShader>("res/shaders/butterflyCompute.glsl");
		displacement_Shader = std::make_unique<ComputeShader>("res/shaders/last.glsl");
		creatNormal_Shader = std::make_unique<ComputeShader>("res/shaders/creatNormal.glsl");
		

		//Dxyz_Shader = std::make_unique<ComputeShader>("res/shaders/Dxyz.glsl");
		Dxyz_Shader = std::make_unique<ComputeShader>("res/shaders/signal.glsl");
		gass_Texture_Shader = std::make_unique<ComputeShader>("res/shaders/gass.glsl");
		IFFT = std::make_unique<ComputeShader>("res/shaders/ifft.glsl");


		pk_Texture = std::make_unique<mTexture>(512,512);
		//gass_Texture = std::make_unique<mTexture>(512, 512);
		gass_Texture = std::make_unique<mTexture>(512, 512,gass.data());
		hkt_dy_Texture = std::make_unique<mTexture>(512, 512);
		hkt_dx_Texture = std::make_unique<mTexture>(512, 512);
		hkt_dz_Texture = std::make_unique<mTexture>(512, 512);
		displacement_Y_Texture = std::make_unique<mTexture>(512, 512);
		displacement_X_Texture = std::make_unique<mTexture>(512, 512);
		displacement_Z_Texture = std::make_unique<mTexture>(512, 512);
		Dxyz_Texture = std::make_unique<mTexture>(512, 512);
		normalmap = std::make_unique<mTexture>(512, 512);

		butterfly_Texture = std::make_unique<mTexture>(9, 512);

		pingpong0 = std::make_unique<mTexture>(512, 512);
		pingpong1 = std::make_unique<mTexture>(512, 512);
		temp_Texture = std::make_unique<mTexture>(512, 512);

		Ssbo = std::make_unique<SSBO>(in, sizeof(int)*512);
	//	gass_ssbo = std::make_unique<SSBO>(gass, sizeof(gass));

		for (int i = 0; i < 512; i++)
		{
		//	std::cout << in[i] << std::endl;
		}
		
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPatchParameteri(GL_PATCH_VERTICES, 4);

		pk_Texture->cBind(0);
		gass_Texture->cBind(1);
		h0k_k_Shader->use();

		h0k_k_Shader->setInt("N", 512);
		h0k_k_Shader->setInt("L", 1024);
		h0k_k_Shader->setFloat("A", 0.000003f);//0.000003f
		h0k_k_Shader->setVec2("windDirection", glm::vec2(1, 1));
		h0k_k_Shader->setFloat("windspeed", 40);

		glDispatchCompute(512 / 32, 512 / 32, 1);
		glFinish();

	}

	TestClearColor::~TestClearColor()
	{
		
	}
	void TestClearColor::FourierTransform(GLuint spectrum, GLuint tempdata, std::unique_ptr<ComputeShader>& shader)
	{
		// horizontal pass
		glBindImageTexture(0, spectrum, 0, GL_TRUE, 0, GL_READ_ONLY, GL_RGBA32F);
		glBindImageTexture(1, tempdata, 0, GL_TRUE, 0, GL_WRITE_ONLY, GL_RGBA32F);

		shader->use();
		shader->setInt("readbuff", 0);
		shader->setInt("writebuff", 1);

		glDispatchCompute(512, 1, 1);

		glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

		// vertical pass
		glBindImageTexture(0, tempdata, 0, GL_TRUE, 0, GL_READ_ONLY, GL_RGBA32F);
		glBindImageTexture(1, spectrum, 0, GL_TRUE, 0, GL_WRITE_ONLY, GL_RGBA32F);

		shader->use();
		shader->setInt("readbuff", 0);
		shader->setInt("writebuff", 1);
		glDispatchCompute(512, 1, 1);
		glFinish();
	}

	void TestClearColor::displament() {
		FourierTransform(hkt_dx_Texture->m_RendererID, temp_Texture->m_RendererID, IFFT);
		FourierTransform(hkt_dy_Texture->m_RendererID, temp_Texture->m_RendererID, IFFT);
		FourierTransform(hkt_dz_Texture->m_RendererID, temp_Texture->m_RendererID, IFFT);
	}

	void TestClearColor::OnUpdate(float deltaTime)
	{
		/*
		gass_Texture->cBind(0);
	//	gass_ssbo->Bind(1);
		//gass_Shader->use();
		gass_Texture_Shader->use();
		glDispatchCompute(512/32, 512/32, 1);		
		glFinish();
		*/
		

		pk_Texture->cBind(0);
		hkt_dy_Texture->cBind(1);
		hkt_dx_Texture->cBind(2);
		hkt_dz_Texture->cBind(3);
		dxyz_Shader->use();
		dxyz_Shader->setInt("N", 512);
		dxyz_Shader->setInt("L", 1024);
		dxyz_Shader->setFloat("t", deltaTime*3);

		glDispatchCompute(512 / 32, 512 / 32, 1);
		glFinish();

		/*
		butterfly_Texture->cBind(0);
		Ssbo->Bind(1);
		Butterfly_T_Shader->use();
		Butterfly_T_Shader->setInt("N", 512);

		glDispatchCompute(9, 512/32,1);
		glFinish();
		*/

		/*
		for(int j=0;j<3;j++)
		{
			butterfly_Compute_Shader->use();
			butterfly_Texture->cBind(0);
			//pingpong0->cBind(1);
			if (j==0)
			{
				hkt_dy_Texture->cBind(1);
			}
			else if (j == 1)
			{
				hkt_dx_Texture->cBind(1);
			}
			else
			{
				hkt_dz_Texture->cBind(1);
			}
			
			pingpong1->cBind(2);

			int pingpong = 0;
			butterfly_Compute_Shader->setInt("direction", 0);
			for (int i = 0; i < 9; i++)
			{

				//特殊处理
				if (i == 0) {
					butterfly_Compute_Shader->setInt("stage", i);
					butterfly_Compute_Shader->setInt("pingpong", pingpong);

					pingpong += 1;
					pingpong = pingpong % 2;


					glDispatchCompute(512 / 32, 512 / 32, 1);
					glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

				}
				else
				{
					pingpong0->cBind(1);
					butterfly_Compute_Shader->setInt("stage", i);
					butterfly_Compute_Shader->setInt("pingpong", pingpong);

					pingpong += 1;
					pingpong = pingpong % 2;

					glDispatchCompute(512 / 32, 512 / 32, 1);
					glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
				}
			}

			butterfly_Compute_Shader->setInt("direction", 1);
			for (int i = 0; i < 9; i++)
			{
				butterfly_Compute_Shader->setInt("stage", i);
				butterfly_Compute_Shader->setInt("pingpong", pingpong);

				pingpong += 1;
				pingpong = pingpong % 2;


				glDispatchCompute(512 / 32, 512 / 32, 1);
				glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

			}
			glFinish();

			displacement_Shader->use();
			displacement_Shader->setInt("N", 512);
			displacement_Shader->setInt("pingpong", pingpong);

			if (j == 0)
			{
				displacement_Y_Texture->cBind(0);
			}
			else if (j == 1)
			{
				displacement_X_Texture->cBind(0);
			}
			else
			{
				displacement_Z_Texture->cBind(0);
			}
		
			pingpong0->cBind(1);
			pingpong1->cBind(2);
			glDispatchCompute(512 / 32, 512 / 32, 1);
			glFinish();





		Dxyz_Shader->use();
		displacement_X_Texture->cBind(0);
		displacement_Y_Texture->cBind(1);
		displacement_Z_Texture->cBind(2);
		Dxyz_Texture->cBind(3);
		glDispatchCompute(512 / 32, 512 / 32, 1);
		glFinish();
		}
		*/
		
		
		FourierTransform(hkt_dx_Texture->m_RendererID, temp_Texture->m_RendererID, IFFT);
		FourierTransform(hkt_dy_Texture->m_RendererID, temp_Texture->m_RendererID, IFFT);
		FourierTransform(hkt_dz_Texture->m_RendererID, temp_Texture->m_RendererID, IFFT);
		

		
		Dxyz_Shader->use();
		
		hkt_dx_Texture->cBind(0);
		hkt_dy_Texture->cBind(1);
		hkt_dz_Texture->cBind(2);
		Dxyz_Texture->cBind(3);
		
		glDispatchCompute(512 / 32, 512 / 32, 1);
		glFinish();
	

		creatNormal_Shader->use();
		Dxyz_Texture->cBind(0);
		normalmap->cBind(1);
		glDispatchCompute(512 / 32, 512 / 32, 1);
		glFinish();

		displacement_X_Texture->Bind();
		ImGui::Image((void*)displacement_X_Texture->m_RendererID, ImVec2(64.0f, 64.0f));

		
	}

	void TestClearColor::OnRnder()
	{
		glViewport(0, 0, 800, 600);
		projection = glm::perspective(glm::radians(m_Camera.Zoom), (float)800 / (float)600, 0.1f, 100000.0f);
		view = m_Camera.GetViewMat();

		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	{
		glDepthMask(GL_FALSE);
		cubeMap_Shader->Bind();
		cubeMap_Shader->SetUniform1i("skybox", 0);
		cubeMap_Shader->SetUniformMat4f("projection", projection);
		cubeMap_Shader->SetUniformMat4f("view", glm::mat4(glm::mat3(m_Camera.GetViewMat())));
		cubeMap->Bind(0);

		cubeMap_Vao->Bind();

		glDrawArrays(GL_TRIANGLES, 0, 36);
		glDepthMask(GL_TRUE);
	}
	//	hkt_dx_Texture->Bind(0);
	//	hkt_dy_Texture->Bind(1);
	//	hkt_dz_Texture->Bind(2);
	
		Dxyz_Texture->Bind(0);
		normalmap->Bind(1);
		cubeMap->Bind(2);

		m_Shader->Bind();
		m_Shader->SetUniform1i("u_displacementMap", 0);

		m_Shader->SetUniform1i("u_normal", 1);
		m_Shader->SetUniform1i("envmap", 2);
		
		m_Shader->SetUniformMat4f("projection", projection);
		m_Shader->SetUniformMat4f("view", view);
		m_Shader->SetUniformMat4f("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
	//	m_Shader->SetUniform3f("lightColor", 1, 1, 1);
	//	m_Shader->SetUniform3f("lightPos", 100.0, 300.0, 100.0);
		m_Shader->SetUniform3f("eyePos", m_Camera.cameraPos);
		m_Vao->Bind();
		//glDrawArrays(GL_PATCHES, 0, 4);
		

		//glDrawArrays(GL_TRIANGLES, 0, 511*511*2);
		glDrawElements(GL_TRIANGLES, (N - 1) * (N - 1) * 6, GL_UNSIGNED_INT, indices.data());

		t_Shader->Bind();
//	    hkt_dx_Texture->Bind(0);
//		hkt_dy_Texture->Bind(1);
//		hkt_dz_Texture->Bind(2);
	//	pk_Texture->Bind(0);
		hkt_dx_Texture->cBind(0);
		
		normalmap->Bind(1);
		gass_Texture->Bind(2);
		pk_Texture->Bind(3);
		
		t_Vao->Bind();
		for (int i = 0; i < 4; i++)
		{
			
			t_Shader->SetUniform1f("m",  i);
			t_Shader->SetUniform1i("heightMap", i);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}		
	}

	void TestClearColor::OnimGuiRender()
	{
		
		//m_Texture->Bind(0);
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
		ImGui::SliderFloat("Wind Magnitude", &wind_magnitude, 10.f, 50.f);
		ImGui::SliderFloat("Wind Angle", &wind_angle, 0, 359);
			
	}
	
}