#include "pch.h"
#include "Panels/MainPanel.h"

#include "Core/App.h"

void MainPanel::OnRender()
{
	App& app = App::Get();
	unsigned int windowWidth = app.GetWindow().GetWidth();
	unsigned int windowHeight = app.GetWindow().GetHeight();

	ImGuiWindowFlags windowFlags =
		  ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoCollapse
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus
		| ImGuiWindowFlags_NoNavFocus
	;

	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
	ImGui::SetNextWindowSize(ImVec2((float)windowWidth, (float)windowHeight));

	ImGui::Begin("Main Window", nullptr, windowFlags);
	ImGui::End();
}
