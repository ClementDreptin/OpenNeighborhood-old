#include "pch.h"
#include "Elements/PathNode.h"

#include "Xbox/XboxManager.h"
#include "Panels/PathPanel.h"
#include "Elements/File.h"
#include "Render/UI.h"

PathNode::PathNode(const std::string& label, size_t posInPath, void* parentPanel)
	: Element(label, "", "Couldn't access directory"), m_PosInPath(posInPath), m_ParentPanel(parentPanel) {}

void PathNode::OnRender()
{
	if (ImGui::Button(m_Label.c_str()))
		OnClick();

	ImGui::PushFont(UI::GetRegularFont());
	DisplayErrorModal();
	ImGui::PopFont();
}

void PathNode::OnClick()
{
	std::string newXboxLocation;

	for (size_t i = 0; i <= m_PosInPath; i++)
	{
		newXboxLocation += ((PathPanel*)m_ParentPanel)->m_PathNodes[i].GetLabel();

		if (i < m_PosInPath)
			newXboxLocation += '\\';
	}

	XBDM::Console& xbox = XboxManager::GetConsole();
	std::set<XBDM::File> files;

	try
	{
		// If the new location ends with ':', then it's a drive and we need to add '\' at the end
		files = xbox.GetDirectoryContents(newXboxLocation.back() == ':' ? newXboxLocation + '\\' : newXboxLocation);
	}
	catch (const std::exception& exception)
	{
		m_ErrorMessage = exception.what();
		m_Success = false;
	}

	if (!m_Success)
		return;

	XboxManager::SetCurrentLocation(newXboxLocation);

	auto fileElements = CreateRef<std::vector<Ref<Element>>>();

	for (auto& file : files)
		fileElements->emplace_back(CreateRef<File>(file));

	ContentsChangeEvent event(fileElements);
	m_EventCallback(event);
};
