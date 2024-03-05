#include "Audio.hxx"
#include "TypeConversion.hxx"
#include <ctime>
#include <msclr\marshal_cppstd.h>

using namespace TDS::AudioWerks;

namespace ScriptAPI
{
	AudioSource::AudioSource()
	{
		audio_engine = AudioEngine::AudioEngine::get_audioengine_instance();
		deltatime = 0.f;
		wait = 0;
		//clips = gcnew System::Collections::SortedList<System::String^, AudioComponent^>();
	}

	void AudioSource::AddClips(AudioComponent clip)
	{
		clips->Add(toSystemString(clip.getFilePath()), clip);
	}
	
	void AudioSource::Play(System::String^ clip, unsigned int delay)
	{		
		/*msclr::interop::marshal_context context;
		TDS::SoundInfo temp = context.marshal_as<TDS::SoundInfo>(clip);*/

		TDS::SoundInfo temp(toStdString(clip));

		audio_engine->FadeInSound(delay, temp);
	}

	void AudioSource::Play(System::String^ clip)
	{
		TDS::SoundInfo temp(toStdString(clip));

		audio_engine->playSound(temp);
	}

	void AudioSource::Pause(System::String^ clip)
	{
		TDS::SoundInfo temp(toStdString(clip));

		audio_engine->pauseSound(temp);
	}

	void AudioSource::Stop(System::String^ clip)
	{
		TDS::SoundInfo temp(toStdString(clip));

		audio_engine->stopSound(temp);
	}

	void AudioSource::StopAll()
	{
		audio_engine->stopAllSound();
	}

	/*float AudioSource::get_volume()
	{

	}

	void AudioSource::set_volume(float vol)
	{

	}*/

	void AudioSource::Loop(bool set)
	{
		
	}

	bool AudioSource::finished(System::String^ clip)
	{
		TDS::SoundInfo* temp = audio_engine->findSound(toStdString(clip));

		return audio_engine->soundFinished(*temp);
	}

	/*float AudioSource::get_pitch()
	{

	}

	void AudioSource::set_pitch(float vol)
	{

	}*/

	//template<typename T>
	//T& AudioSource::operator=(float val)
	//{
	//	value = val;
	//}

	void AudioSource::SetListenerPos(Vector3 pos, Vector3 forward, Vector3 Up)
	{
		audio_engine->set3DListenerPosition(pos.X, pos.Y, pos.Z, forward.X, forward.Y, forward.Z, Up.X, Up.Y, Up.Z);
	}

	void AudioSource::SetSoundPos(Vector3 pos, System::String^ name)
	{
		audio_engine->update3DSoundPosition(pos.toVec3(), *audio_engine->findSound(toStdString(name)));
	}

	void AudioSource::GetListener(Vector3& pos, Vector3& velocity, Vector3& forward, Vector3& up)
	{
		TDS::Vec3 tpos, tvel, tfor, tup;
		audio_engine->get3DListenerCharacteristics(tpos, tvel, tfor, tup);

		pos = Vector3(tpos.x, tpos.y, tpos.z);
		velocity = Vector3(tvel.x, tvel.y, tvel.z);
		forward = Vector3(tfor.x, tfor.y, tfor.z);
		up = Vector3(tup.x, tup.y, tup.z);
	}
}