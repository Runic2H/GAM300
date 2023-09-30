#include "imguiHelper/ImguiConsole.h"
#include "imguiHelper/ImguiAssetBrowser.h"

namespace TDS
{
	EditorConsole::EditorConsole()
	{
		//selected = 0;
		//selectedFolder = -1;
		//renameCheck = false;

		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Console";
		windowPadding = ImVec2(0.f, 0.f);
		AddLog("-------------- ImGui Console Start --------------");

		//insertEntities();
	}

	void EditorConsole::ClearLog()
	{
		for (int i = 0; i < Items.Size; i++)
			free(Items[i]);
		Items.clear();
	}

	static char* Strdup(const char* str) { size_t len = strlen(str) + 1; void* buf = malloc(len); IM_ASSERT(buf); return (char*)memcpy(buf, (const void*)str, len); }


	void EditorConsole::AddLog(const char* fmt, ...) IM_FMTARGS(2) 
	{
		// FIXME-OPT
		char buf[1024];
		va_list args;
		va_start(args, fmt);
		vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
		buf[IM_ARRAYSIZE(buf) - 1] = 0;
		va_end(args);
		Items.push_back(Strdup(buf));
	}

	void EditorConsole::update()
	{
		ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
		if (ImGui::Button("Clear"))ClearLog(); ImGui::SameLine();
		bool copy_to_clipboard = ImGui::Button("Copy");

		ImGui::Separator();

		const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
		ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
		if (ImGui::BeginPopupContextWindow())
		{
			if (ImGui::Selectable("Clear")) ClearLog();
			ImGui::EndPopup();
		}
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
		if (copy_to_clipboard)
			ImGui::LogToClipboard();
		for (int i = 0; i < Items.Size; i++)
		{
			const char* item = Items[i];
			//if (!Filter.PassFilter(item))
			continue;

			// Normally you would store more information in your item (e.g. make Items[] an array of structure, store color/type etc.)
			bool pop_color = false;
			if (strstr(item, "[error]")) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.4f, 0.4f, 1.0f)); pop_color = true; }
			else if (strncmp(item, "# ", 2) == 0) { ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.8f, 0.6f, 1.0f)); pop_color = true; }
			ImGui::TextUnformatted(item);
			if (pop_color)
				ImGui::PopStyleColor();
		}
		if (copy_to_clipboard)
			ImGui::LogFinish();

		//if (ScrollToBottom || (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()))
		ImGui::SetScrollHereY(1.0f);
		//ScrollToBottom = false;

		for (int i = 0; i < Items.Size; i++) {
			const char* item = Items[i];

			ImVec4 color;
			bool   has_color = false;
			if (strstr(item, "[info]")) {
				color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				has_color = true;
			}
			else if (strstr(item, "[yellow]")) {
				color = ImVec4(1.0f, 0.8f, 0.0f, 1.0f);
				has_color = true;
			}
			else if (strstr(item, "[orange]")) {
				color = ImVec4(0.8f, 0.2f, 0.0f, 1.0f);
				has_color = true;
			}
			else {
				color = ImVec4(1.0f, 0.8f, 0.6f, 1.0f);
				has_color = true;
			}
			if (has_color)
				ImGui::PushStyleColor(ImGuiCol_Text, color);
			ImGui::TextUnformatted(item);
			if (has_color)
				ImGui::PopStyleColor();
		}

		ImGui::SetScrollHereY(1.0f);

		//ImGui::SetCursorPos({ pos.x + size.x - 66, pos.x + size.y - 36 });


		//some things to test the console
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		if (io.WantCaptureMouseUnlessPopupClose == false)
		{
			if (ImGui::IsMouseClicked(0))
			{
				AddLog("[yellow] Mouse Click detected on Viewport");
			}
		}
		//set this to only capture mouse presses on the window
		if (io.WantCaptureMouseUnlessPopupClose == true)
		{
			if (ImGui::IsMouseClicked(0))
			{
				AddLog("[orange] Mouse Click detected on ImGui Window ");
				//std::cout << AssetBrowser::m_curr_path << std::endl;
			}
		}
		if (ImGui::IsKeyPressed(ImGuiKey_UpArrow))
		{
			AddLog("Up key pressed");
		}
		if (ImGui::IsKeyPressed(ImGuiKey_DownArrow))
		{
			AddLog("Down key pressed");
		}
		if (ImGui::IsKeyPressed(ImGuiKey_LeftArrow))
		{
			AddLog("Left key pressed");
		}
		if (ImGui::IsKeyPressed(ImGuiKey_RightArrow))
		{
			AddLog("[info] Right key pressed");
		}


		ImGui::PopStyleVar();
		ImGui::EndChild();

	}
}