#pragma once

#include"Test.h"

namespace test {
	class TestClearColor:public Test
	{
	public:
		TestClearColor();
		~TestClearColor();

		virtual void OnUpdate(float deltaTime) override;
		virtual void OnRnder() override;
		virtual void OnimGuiRender() override;
	private:
		float m_ClearColor[4];

	};

}