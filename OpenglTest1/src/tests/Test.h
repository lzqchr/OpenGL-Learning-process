#pragma once
#include<functional>
#include<vector>
#include<iostream>
#include"Camera.h"
namespace test {
	class Test
	{
	
	public:
		Test(){  };
		virtual ~Test() {}
		virtual void OnUpdate(float deltaTime){}
		virtual void OnRnder(){}
		virtual void OnimGuiRender(){}
	private:
	protected:
	};
	class TestMenu :public Test 
	{
	public:
		TestMenu(Test*& currentTestPointer) ;
		
		void OnimGuiRender() override; 
	
		template<typename T>
		void RegisterTest(const std::string& name, Camera& camera)
		{
			std::cout << "Registering test" << name << std::endl;

			m_Tests.push_back(std::make_pair(name, [&camera]() {return new T( camera); }));
		}
	private:
		Test*& m_CurrentTest;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;

	
	};

}