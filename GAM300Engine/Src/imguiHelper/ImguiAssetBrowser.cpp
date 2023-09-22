#include "imguiHelper/ImguiAssetBrowser.h"

namespace TDS
{
	AssetBrowser::AssetBrowser()
	{
		//selected = 0;
		//selectedFolder = -1;
		//renameCheck = false;

		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Asset Browser";
		windowPadding = ImVec2(0.f, 0.f);

		//insertEntities();
	}

	void AssetBrowser::update()
	{

	}
}