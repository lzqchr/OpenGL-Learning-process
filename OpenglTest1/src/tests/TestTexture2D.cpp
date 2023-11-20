#include"TestTexture2D.h"
#include<GL/glew.h>
#include"Render.h"
#include"imgui/imgui.h"
#include"glm/glm.hpp"
#include"glm/gtc/matrix_transform.hpp"
#include"glfw3.h"
#include<iostream>
namespace test {



    TestTexture2D::TestTexture2D(Camera& m_camera) : camera(m_camera) 
	{
        

        float cubeVertices[] = {
            // positions          // normals           // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
            -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
        };
        float planeVertices[] = {
            // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
             5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,

             5.0f, -0.5f,  5.0f,  1.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 1.0f,
             5.0f, -0.5f, -5.0f,  1.0f, 1.0f
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
        /*
        VertexBuffer cubeVb(cubeVertices, 8 * 6 * 6 * sizeof(float));
        VertexBuffer planeVb(planeVertices, 5 * 3 * 2 * sizeof(float));
        */


        glm::vec3 lightPos(0.0f, 0.0f, 0.0f);

        m_CubeShader = std::make_unique<Shader>("res/shaders/cube.shader");
        m_GroundShader = std::make_unique<Shader>("res/shaders/ground.shader");
        m_LightShader = std::make_unique<Shader>("res/shaders/Light.shader");
        m_CubemapShader = std::make_unique<Shader>("res/shaders/cubeMap.shader");

        m_CubeVao = std::make_unique<VertexArray>();
        m_GroundVao = std::make_unique<VertexArray>();
        m_CubeMapVao = std::make_unique<VertexArray>();

        m_CubeVbo = std::make_unique<VertexBuffer>(cubeVertices, 8 * 6 * 6 * sizeof(float));
        m_GroundVbo = std::make_unique<VertexBuffer>(planeVertices, 5 * 3 * 2 * sizeof(float));
        m_CubeMapVbo = std::make_unique<VertexBuffer>(skyboxVertices, 3* 6 * 6 * sizeof(float));

        m_CubeTexture1 = std::make_unique<mTexture>("res/textures/box.png");
        m_CubeTexture2 = std::make_unique<mTexture>("res/textures/specular.png");
        m_GroundTexture1 = std::make_unique<mTexture>("res/textures/ground.png");
        m_Cubemap = std::make_unique<CubeMap>(faces);

        {
            projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
            view = camera.GetViewMat();
        }

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        //…Ó∂»ºÏ≤‚
        glEnable(GL_DEPTH_TEST);

        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(3);
        layout.Push<float>(2);
        m_CubeVao->AddBuffer(*m_CubeVbo, layout);

        VertexBufferLayout planeLayout;
        planeLayout.Push<float>(3);
        planeLayout.Push<float>(2);
        m_GroundVao->AddBuffer(*m_GroundVbo, planeLayout);

        VertexBufferLayout cubeMapLayout;
        cubeMapLayout.Push<float>(3);
        m_CubeMapVao->AddBuffer(*m_CubeMapVbo, cubeMapLayout); 

        m_CubeShader->Bind();
        m_CubeShader->SetUniform1i("material.diffuse", 0);
        m_CubeShader->SetUniform1i("material.specular", 1);

        // light properties
        m_CubeShader->SetUniform3f("light.ambient", 0.2f, 0.2f, 0.2f);
        m_CubeShader->SetUniform3f("light.diffuse", 0.5f, 0.5f, 0.5f);
        m_CubeShader->SetUniform3f("light.specular", 1.0f, 1.0f, 1.0f);
        m_CubeShader->SetUniform3f("light.position", 1.0f, 1.0f, 1.0f);

        m_CubemapShader->Bind();
        m_CubemapShader->SetUniform1i("skybox", 0);

	}

	TestTexture2D::~TestTexture2D()
	{
	}

	void TestTexture2D::OnUpdate(float deltaTime)
	{
        projection = glm::perspective(glm::radians(camera.Zoom), (float)800 / (float)600, 0.1f, 100.0f);
        view = camera.GetViewMat();
        lightPos.x =  sin(glfwGetTime()) * 2.0f;
        lightPos.y =sin(glfwGetTime() / 2.0f) * 1.0f;

	}

	void TestTexture2D::OnRnder()
	{
		GLCall(glClearColor(0.0,0.0,0.0,1));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

        Render renderer;

        glDepthMask(GL_FALSE);
        m_Cubemap->Bind();

        {
            m_CubemapShader->Bind();
            m_CubemapShader->SetUniform1i("skybox", 0);
            m_CubemapShader->SetUniformMat4f("projection", projection);
            m_CubemapShader->SetUniformMat4f("view", glm::mat4(glm::mat3(camera.GetViewMat())));

            m_CubeMapVao->Bind();
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glDepthMask(GL_TRUE);

        m_CubeTexture1->Bind(0);
        m_CubeTexture2->Bind(1);
        {
            

            m_CubeShader->Bind();
            
            m_CubeShader->SetUniformMat4f("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
            m_CubeShader->SetUniformMat4f("projection", projection);
            m_CubeShader->SetUniformMat4f("view", view);

            m_CubeShader->SetUniform3f("light.position", lightPos);

            m_CubeShader->SetUniform3f("light.ambient",ambient);
            m_CubeShader->SetUniform3f("light.diffuse",diffuse);
            m_CubeShader->SetUniform3f("light.specular",specular);

            m_CubeShader->SetUniform1f("material.shininess", 64.0f);

            m_CubeVao->Bind();
           

            GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));

            m_LightShader->Bind();
            glm::mat4 model1 = glm::mat4(1.0f);
            model1 = glm::translate(model1, lightPos);
            model1 = glm::scale(model1, glm::vec3(0.2f));

            m_LightShader->SetUniformMat4f("u_Model", model1);
            m_LightShader->SetUniformMat4f("u_View",view);
            m_LightShader->SetUniformMat4f("u_Pro",projection);
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
        }
        m_GroundTexture1->Bind();
        {
            m_GroundShader->Bind();

            m_GroundShader->SetUniformMat4f("model", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f)));
            m_GroundShader->SetUniformMat4f("projection", projection);
            m_GroundShader->SetUniformMat4f("view", view);

            m_GroundVao->Bind();
            GLCall(glDrawArrays(GL_TRIANGLES, 0, 6));
        }
       
        
        
	}

	void TestTexture2D::OnimGuiRender()
	{
        ImGui::ColorEdit3("ambient",(float*)&ambient);
        ImGui::ColorEdit3("diffuse", (float*)&diffuse);
        ImGui::ColorEdit3("specular", (float*)&specular);
        ImGui::SliderFloat("shininess", &shininess,0,100);
	}

}