#pragma once
#include "IncludeFromEngine.hxx"
#include <fmod_engine/AudioEngine.h>
#include <components/SoundInfo.h>
#include <filesystem>

namespace ScriptAPI
{
    public ref class AudioClip
    {
    public:        
        void add_clips(System::String^ filePath);
        
        System::Collections::Generic::List<System::String^> clips;
        int sub;
    };
    
    public ref class AudioSource
    {
    //public:
    //    static ref struct volume
    //    {
    //        float value;
    //    };
    //    
    //    static ref struct pitch
    //    {
    //        float value;
    //    };

    public:
        AudioSource();
        
        static void Play(unsigned long delay);
        static void Pause();
        static void Stop();
        static void StopAll();

        /*float get_volume();
        void set_volume(float vol);*/
        static void Loop(bool set);
        static bool enabled();
        /*float get_pitch();
        void set_pitch(float set);*/

        //template<typename T>
        //T& operator=(float val);

        static AudioClip^ clip; //AudioClips are attached to AudioSource
        static TDS::AudioWerks::AudioEngine* audio_engine;
        static unsigned long wait;
        static float deltatime;
    };
}