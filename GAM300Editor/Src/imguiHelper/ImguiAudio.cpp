/*!*************************************************************************
****
\file ImguiAudio.cpp
\author w.chongsheng
\par DP email: w.chongsheng@digipen.edu
\par Course: CSD3400
\par Section: a
\brief  Imgui UI in charge of audio manipulations
****************************************************************************
***/

#include "imguiHelper/ImguiAudio.h"
#include <string.h>

namespace TDS
{
	AudioImgui::AudioImgui()
	{
		flags = NULL;
		panelTitle = "Audio Files";
		windowPadding = ImVec2(0.f, 0.f);

		appear = false;
		bar = 0.f;

		music.clear();
		SFX.clear();
		background.clear();
		VO.clear();

		std::cout << "AudImg Constructor" << '\n';

		audeng = audeng = AudioWerks::AudioEngine::get_audioengine_instance();
	}

	AudioImgui::~AudioImgui()
	{
		delete audeng;
	}

	bool& AudioImgui::ToggleControls(bool state)
	{
		appear = state;

		if (appear)
		{
			flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoCollapse;
		}
		else
		{
			flags = ImGuiWindowFlags_None;
			
			for(SoundInfo& sort : music)
			{
				audeng->stopSound(sort);
			}
			for (SoundInfo& sort : SFX)
			{
				audeng->stopSound(sort);
			}
			for (SoundInfo& sort : background)
			{
				audeng->stopSound(sort);
			}
			for (SoundInfo& sort : VO)
			{
				audeng->stopSound(sort);
			}
		}

		return appear;
	}

	void AudioImgui::add_audio_files(std::filesystem::path folder_path)
	{
		std::filesystem::path append = folder_path;
		std::cout << "The file path is " << append.string() << '\n';

		std::filesystem::path pathing("../../assets");
		std::filesystem::path full_path = pathing / append;
		std::vector<std::filesystem::path> all_files;

		if (std::filesystem::is_directory(full_path))
		{
			all_files = go_deeper(full_path);
		}

		for (auto& temp : all_files)
		{
			std::cout << "Files: " << temp.string() << '\n';
		}

		for (auto& str : all_files)
		{
			if (str.string().find("Music"))
			{
				SoundInfo temp(str.string());
				temp.setLoop(false);
				temp.set3DCoords(0.f, 0.f, 0.f);
				temp.setVolume(0.5f);

				background.push_back(temp);
			}
			else if (str.string().find("Songs"))
			{
				SoundInfo temp(str.string());
				temp.setLoop(false);
				temp.set3DCoords(0.f, 0.f, 0.f);
				temp.setVolume(0.5f);

				music.push_back(temp);
			}
			else if (str.string().find("Sound Effects"))
			{
				SoundInfo temp(str.string());
				temp.setLoop(false);
				temp.set3DCoords(0.f, 0.f, 0.f);
				temp.setVolume(0.5f);

				SFX.push_back(temp);
			}
			else if (str.string().find("Voice Overs"))
			{
				SoundInfo temp(str.string());
				temp.setLoop(false);
				temp.set3DCoords(0.f, 0.f, 0.f);
				temp.setVolume(0.5f);

				VO.push_back(temp);
			}
		}

		/*SoundInfo add_sound(pathing.string());
		music.push_back(add_sound);
		add_sound.setLoop(false);
		add_sound.set3DCoords(0.f, 0.f, 0.f);
		add_sound.setVolume(0.5f);
		music.push_back(add_sound);*/

		/*SoundInfo test_path("../../assets/audioFiles/Songs/test.flac");
		test_path.setLoop(false);
		test_path.set3DCoords(0.f, 0.f, 0.f);
		test_path.setVolume(0.5f);

		music.push_back(test_path);*/
	}

	std::vector<std::filesystem::path> AudioImgui::go_deeper(std::filesystem::path f_path)
	{
		std::vector<std::filesystem::path> folders;
		std::vector<std::filesystem::path> files;

		for (auto& temp : std::filesystem::directory_iterator(f_path))
		{
			if (temp.is_directory())
			{
				folders = go_deeper(temp);

				for (const auto& temp2 : folders)
				{
					files.push_back(temp2);
				}
			}
			else
			{
				files.push_back(temp);
			}
		}

		return files;
	}

	void AudioImgui::play(std::string file)
	{
		
		
		audeng->loadSound(temp);
		audeng->playSound(temp);

		/*audeng->loadSound(add_sound);
		audeng->playSound(add_sound);*/
	}

	void AudioImgui::update()
	{
		if (appear)
		{
			ImGui::Text("Controls: ");
			ImGui::SameLine();

			if(ImGui::Selectable("Play Song"))
			{
				if (ImGui::ArrowButton("Play", ImGuiDir_Right))
				{
					/*SoundInfo selected{};
					selected = ImGui::IsItemClicked();
					
					audeng->playSound();*/
				}
			}

			ImGui::Columns(3);
			ImGui::SliderFloat("Playback", &bar, 16, 512);
		}

		audeng->update();
	}
}