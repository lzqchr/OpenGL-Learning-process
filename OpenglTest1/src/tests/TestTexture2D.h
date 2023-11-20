#pragma once

#include"Test.h"
#include"Camera.h"
#include"VertexBufferLayout.h"
#include"mTexture.h"
#include"CubeMap.h"


#include<memory>
namespace test {
	class TestTexture2D:public Test
	{
	public:
		TestTexture2D(Camera& m_camera);
		~TestTexture2D();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRnder() override;
		virtual void OnimGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_CubeVao,m_GroundVao,m_CubeMapVao;
		std::unique_ptr <VertexBuffer> m_CubeVbo,m_GroundVbo, m_CubeMapVbo;//实例和gpu保存 实例消失gpu数据消失
		std::unique_ptr <Shader> m_CubeShader,m_GroundShader,m_LightShader,m_CubemapShader;
		std::unique_ptr<mTexture>m_CubeTexture1, m_CubeTexture2, m_GroundTexture1;
		std::unique_ptr<CubeMap>m_Cubemap;
		
		
		Camera& camera;
		glm::mat4 projection, view;
		glm::vec3 lightPos= glm::vec3(0.0f, 0.0f, 0.0f),ambient=glm::vec3(1.0f,1.0f,1.0f), diffuse, specular;
		float shininess;
	
		std::vector<std::string> faces{
		"res/skybox/right.jpg",
		"res/skybox/left.jpg",
		"res/skybox/top.jpg",
		"res/skybox/bottom.jpg",
		"res/skybox/front.jpg",
		"res/skybox/back.jpg"
		};
		

	};

}