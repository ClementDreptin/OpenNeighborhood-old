#include "pch.h"
#include "Elements/Element.h"

#include "Render/TextureManager.h"
#include "OpenNeighborhood.h"

Element::Element(const std::string& label, const std::string& textureName, const std::string& errorMessage)
	: m_Label(label), m_TextureName(textureName), m_ErrorMessage(errorMessage)
{
	if (textureName != "")
	{
		if (!TextureManager::TextureExists(textureName))
			TextureManager::AddTexture(textureName, GetExecDir().append("assets/icons/").string() + textureName + ".png");

		auto texture = TextureManager::GetTexture(textureName);
		m_Width = texture->GetWidth() * 3;
		m_Height = texture->GetHeight();
	}

	m_EventCallback = BIND_EVENT_FN(Element::OnEvent);
}

void Element::OnRender()
{
	auto texture = TextureManager::GetTexture(m_TextureName);

	if (ImGui::ImageButtonWithText((void*)(intptr_t)texture->GetTextureID(), ImVec2(texture->GetWidth(), texture->GetHeight()), ImVec2(m_Width, m_Height), m_Label.c_str(), ImVec2(m_Padding, m_Padding)))
		if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			OnClick();

	if (ImGui::BeginPopupContextItem())
	{
		DisplayContextMenu();
		ImGui::EndPopup();
	}

	DisplayConfirmModal();
	DisplayErrorModal();
}

void Element::OnEvent(Event& event)
{
	OpenNeighborhood& currentLayer = OpenNeighborhood::Get();
	currentLayer.OnEvent(event);
}

void Element::DisplayConfirmModal()
{
	if (m_Confirm)
	{
		ImGui::OpenPopup("Confirm");

		ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	}

	if (ImGui::BeginPopupModal("Confirm", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("%s", m_ConfirmMessage.c_str());

		if (ImGui::Button("OK", ImVec2(120.0f, 0.0f)))
		{
			m_ConfirmCallback();
			m_Confirm = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::SameLine();

		if (ImGui::Button("Cancel", ImVec2(120.0f, 0.0f)))
		{
			m_Confirm = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}

void Element::DisplayErrorModal()
{
	if (!m_Success)
	{
		ImGui::OpenPopup("Error");

		ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
		ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	}

	if (ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::Text("%s", m_ErrorMessage.c_str());

		if (ImGui::Button("OK", ImVec2(120.0f, 0.0f)))
		{
			m_Success = true;
			ImGui::CloseCurrentPopup();
		}

		ImGui::EndPopup();
	}
}
