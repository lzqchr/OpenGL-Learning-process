#pragma once
#include<imgui/imgui.h>
#include <glfw3.h>
#include<iostream>
#include<string>
std::string Text = "HELLOW lzqchr";
char textbox[50] = { "text box" };
ImVec4 color;

void DrawGUI() {
	ImGui::Begin(u8"OPENGL²âÊÔ");

	ImDrawList* DrawList = ImGui::GetForegroundDrawList();
	//DrawList->AddRectFilled(ImVec2(0, 0), ImGui::GetMousePos(), ImColor(60, 255, 50));

	ImGui::End();

	ImGui::ShowDemoWindow();
	ImGui::Begin(u8"²âÊÔ");


	//DrawList->AddRectFilled(ImVec2(0, 0), ImGui::GetMousePos(), ImColor(60, 255, 50));

	ImGui::End();

}