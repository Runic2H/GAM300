#include "imguiHelper/ImguiToolbar.h"
#include "imguiHelper/ImguiConsole.h"
#include "imguiHelper/ImguiHierarchy.h"

#include "sceneManager/sceneManager.h"
#include <Windows.h>
#include <shellapi.h>

namespace TDS
{
	/*EditorConsole console;*/ //Wrong method of getting instance
	//std::shared_ptr<EditorConsole> console = static_pointer_cast<EditorConsole>(LevelEditorManager::GetInstance()->panels[PanelTypes::CONSOLE]);

	Toolbar::Toolbar()
	{
		//selected = 0;
		//selectedFolder = -1;
		//renameCheck = false;

		flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		panelTitle = "Toolbar";
		windowPadding = ImVec2(0.f, 0.f);
		

		//insertEntities();
	}

	
	void Toolbar::update()
	{
		ImGui::Text("Display: "); ImGui::SameLine();

		ImGui::SetItemDefaultFocus();
		if (ImGui::ArrowButton("Play", ImGuiDir_Right))
		{
			//console->AddLog("Play button pressed");
			//console->AddLog("Play button pressed");
			//if (isPlay) {
			//	//App->timeManagement->Play();
			//	////TODO: Call the Init of the particles
			//	//App->scene->PlayScene(App->scene->GetRoot(), App->scene->GetRoot());
			//}
			//else if (isPause) {
			//	//set game to resume
			//	//App->timeManagement->Resume();
			//}
			/*App->scene->inGame = true;*/

			if (isPlaying)
			{
				isPlaying = false;
				SceneManager::GetInstance()->loadScene(SceneManager::GetInstance()->getCurrentScene());
			}
			else
			{
				SceneManager::GetInstance()->saveCurrentScene();
				isPlaying = true;
			}
		}
		ImGui::SameLine();
		if (ImGui::Button("||", { 23, 19 }))
		{
			//console->AddLog("Pause button pressed");
			//if (isPause) {
			//	//pause
			//	console->AddLog("Pause button pressed");

			//}

			isPlaying = isPlaying ? false : true;
		}
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8f,0,0,1 });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1,0.2f,0,1 });
		//if (ImGui::Button("STOP", { 40, 19 }))
		//{
		//	console->AddLog("Stop button pressed");
		//	if (isStopped) {

		//		//stop the app
		//		/*App->timeManagement->Stop();
		//		App->scene->inGame = false;
		//		App->scene->StopScene(App->scene->GetRoot(), App->scene->GetRoot());*/
		//	}
		//}
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();


		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f,0,0,1 });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1,0.2f,0,1 });
		if (ImGui::Button("Open FMOD Studio", { 120, 19 }))
		{

			//console->AddLog("Opening fmod");
			if (isOpenFMOD) {

				/*const char* fmodStudioPath = "..\\Dependencies\\FMOD_Studio_2.02.17\\FMOD_Studio.exe";
				const char* command = fmodStudioPath;*/
				ShellExecute(0, L"open", L"..\\Dependencies\\FMOD_Studio_2.02.17\\FMOD_Studio.exe", NULL, NULL, SW_SHOWNORMAL);
			}
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();

		//ImGui::SameLine();
		//ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f,0.1f,0.1f,1 });
		//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1,0.1f,0,1 });
		//if (ImGui::Button("Load Scene", { 100, 19 }))
		//{
		//	console->AddLog("Load Scene Button Pressed");
		//	if (isLoadScene) {


		//	}
		//}
		//ImGui::PopStyleColor();
		//ImGui::PopStyleColor();

		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f,0.1f,0.1f,1 });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1,0.1f,0,1 });
		if (ImGui::Button("Save Scene", { 100, 19 }))
		{
			//console->AddLog("Save Scene Button Pressed");
			if (isSaveScene) {

				std::shared_ptr<Hierarchy> hierarchyPanel = static_pointer_cast<Hierarchy>(LevelEditorManager::GetInstance()->panels[PanelTypes::HIERARCHY]);
				SceneManager::GetInstance()->saveCurrentScene();
			}
		}
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();

		//ImGui::SameLine();
		//ImGui::PushStyleColor(ImGuiCol_Button, { 0.1f,0.1f,0.1f,1 });
		//ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1,0.1f,0,1 });
		//if (ImGui::Button("Add Component", { 100, 19 }))
		//{

		//	console->AddLog("Adding Component");
		//	//do add component
		//}
		//ImGui::PopStyleColor();
		//ImGui::PopStyleColor();
	}
}