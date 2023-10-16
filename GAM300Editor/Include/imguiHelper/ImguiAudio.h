/*!*************************************************************************
****
\file ImguiAudio.h
\author w.chongsheng
\par DP email: w.chongsheng@digipen.edu
\par Course: CSD3400
\par Section: a
\brief  Imgui UI in charge of audio manipulations
****************************************************************************
***/

#ifndef IMGUI_AUDIO
#define IMGUI_AUDIO

#include "ImguiHelper.h"
#include "fmod_engine/AudioEngine.h"

namespace TDS
{
	class AudioImgui : public LevelEditorPanel
	{
	public:
		/**
		 * @brief Constructor that sets appear to false and bar as 0.f. Initiates the Audio Engine.
		*/
		AudioImgui();
		/**
		 * @brief Destructor that deactivates the Audio Engine
		*/
		~AudioImgui();

		/**
		 * @brief Shows ImGui Controls for audio when user navigates to audio assets in the editor.
		*/
		void activate_audio_controls();

		/**
		 * @brief Hides ImGui Constrols for audio.
		*/
		void deactivate_audio_controls();

		/**
		 * @brief Update loop.
		*/
		void update();

	private:
		AudioWerks::AudioEngine audeng;

		bool appear;
		float bar;
	};
}

#endif