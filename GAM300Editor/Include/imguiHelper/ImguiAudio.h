#ifndef IMGUI_AUDIO
#define IMGUI_AUDIO

#include "ImguiHelper.h"
#include "fmod_engine/AudioEngine.h"

namespace TDS
{
	class AudioImgui : public LevelEditorPanel
	{
	public:
		AudioImgui();
		~AudioImgui();

		void update();

	private:
		AudioEngine audeng;
	};
}

#endif