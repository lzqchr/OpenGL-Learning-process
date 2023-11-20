#pragma once

#include"Test.h"
#include"Camera.h"
#include"VertexBufferLayout.h"
#include"mTexture.h"
#include"ComputeShader.h"
#include"Data_obj.h"
#include"CubeMap.h"

#include <cmath>

#include<memory>
namespace test {
	class TestClearColor :public Test
	{
	public:
		TestClearColor(Camera& m_camera);
		~TestClearColor();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRnder() override;
		virtual void OnimGuiRender() override;
		void decToBinary(int n, int binaryNum[], int bits) {
			int i = 0;
			while (n > 0) {
				binaryNum[i] = n % 2;
				n = n / 2;
				i++;
			}
			// 补零
			while (i < bits) {
				binaryNum[i] = 0;
				i++;
			}
		}
		int reverseBinary(int binaryNum[], int bits) {
			int reversed = 0;
			for (int i = 0; i < bits; i++) {
				reversed += binaryNum[i] * pow(2, bits - i - 1);
			}
			return reversed;
		}

		void FourierTransform(GLuint spectrum, GLuint tempdata, std::unique_ptr<ComputeShader>& shader);
		void displament();

	private:
		float m_ClearColor[4];
		float wind_magnitude, wind_angle;
		int ocean_size = 1024;
		glm::mat4 projection, view;
		std::unique_ptr<VertexArray> m_Vao,t_Vao, cubeMap_Vao;
		std::unique_ptr <VertexBuffer> m_Vbo,t_Vbo, cubeMap_Vbo;//实例和gpu保存 实例消失gpu数据消失
		std::unique_ptr <Shader> m_Shader,t_Shader,cubeMap_Shader;
		std::unique_ptr<mTexture>pk_Texture, testTex, gass_Texture, hkt_dy_Texture, hkt_dx_Texture, hkt_dz_Texture, butterfly_Texture, pingpong0, pingpong1;
		std::unique_ptr<mTexture> displacement_Y_Texture, displacement_X_Texture, displacement_Z_Texture, normalmap, Dxyz_Texture;
		std::unique_ptr<mTexture> temp_Texture;

		std::unique_ptr<CubeMap> cubeMap;

		std::unique_ptr<ComputeShader>h0k_k_Shader, gass_Shader, dxyz_Shader, gass_Texture_Shader,
			Butterfly_T_Shader, butterfly_Compute_Shader, displacement_Shader, creatNormal_Shader, Dxyz_Shader,IFFT;
		std::unique_ptr<SSBO>Ssbo;//gass_ssbo;

		std::vector<float> vertices;
	
		std::vector<unsigned int> index;
		//	std::unique_ptr<IndexBuffer> m_IndexBuffer;
		Camera& m_Camera;
		glm::mat4 m_Proj, m_View, model = glm::mat4(1.0f);
		std::vector<float> gass;
		std::vector<int> indices;
		unsigned int EBO;
	//	unsigned int VBO, VAO;
		/*std::vector<std::string> faces{
		"res/skybox/0.jpg",
		"res/skybox/1.jpg",
		"res/skybox/2.jpg",
		"res/skybox/3.jpg",
		"res/skybox/4.jpg",
		"res/skybox/5.jpg"
		};*/

		std::vector<std::string> faces{
		"res/skybox/right.jpg",
		"res/skybox/left.jpg",
		"res/skybox/top.jpg",
		"res/skybox/bottom.jpg",
		"res/skybox/front.jpg",
		"res/skybox/back.jpg"
		};

	protected:

	};

}