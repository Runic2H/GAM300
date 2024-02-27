/*!*************************************************************************
****
\file AudioEngine.cpp
\author w.chongsheng    
\par DP email: w.chongsheng@digipen.edu
\par Course: CSD3400
\par Section: a
\brief  Audio Engine
****************************************************************************
***/

#include <fmod/fmod_errors.h>
#include <iostream>
#include <fmod_engine/AudioEngine.h>

namespace TDS
{
    namespace AudioWerks
    {
        AudioEngine* AudioEngine::audioE_instance = NULL;

        AudioEngine::AudioEngine() : sounds(), loopsPlaying(), soundBanks(),
            eventDescriptions(), eventInstances(), reverb()
        {
            //std::cout << "AudioEngine Constructor" << '\n';
        }

        AudioEngine::~AudioEngine()
        {
            deactivate();
            delete audioE_instance;
            //std::cout << "AudioEngine Destructor" << '\n';
        }

        void AudioEngine::init()
        {
            //std::cout << "FMOD Engine Init" << '\n';
            ERRCHECK(FMOD::System_Create(&lowLevelSystem));
            ERRCHECK(lowLevelSystem->init(MAX_AUDIO_CHANNELS, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0));
            ERRCHECK(FMOD::Studio::System::create(&studioSystem));
            ERRCHECK(studioSystem->getCoreSystem(&lowLevelSystem));
            ERRCHECK(lowLevelSystem->setSoftwareFormat(AUDIO_SAMPLE_RATE, FMOD_SPEAKERMODE_STEREO, 0));
            ERRCHECK(lowLevelSystem->set3DSettings(1.0, DISTANCEFACTOR, 0.5f));
            ERRCHECK(lowLevelSystem->set3DNumListeners(1));
            ERRCHECK(studioSystem->initialize(MAX_AUDIO_CHANNELS, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, 0));
            ERRCHECK(lowLevelSystem->getMasterChannelGroup(&mastergroup));
            initReverb();

            //std::cout << "Audio Engine Init successful!" << '\n';
        }

        void AudioEngine::deactivate()
        {
            ERRCHECK(studioSystem->release());
            ERRCHECK(lowLevelSystem->close());
            ERRCHECK(lowLevelSystem->release());
        }

        AudioEngine* AudioEngine::get_audioengine_instance()
        {            if (audioE_instance == NULL)
            {
                audioE_instance = new AudioEngine();
                audioE_instance->init();
                return audioE_instance;
            }

            return audioE_instance;
        }

        void AudioEngine::update()
        {
            ERRCHECK(studioSystem->update()); // also updates the low level system
        }

        bool AudioEngine::anySoundPlaying()
        {
            bool check{ false };
            
            for (std::pair<unsigned int, FMOD::Channel*> it : normalPlaying)
            {
                it.second->isPlaying(&check);

                if (check)
                {
                    break;
                }
            }
            for (std::pair<unsigned int, FMOD::Channel*> it : loopsPlaying)
            {
                it.second->isPlaying(&check);

                if(check)
                {
                    break;
                }
            }

            return check;
        }

        void AudioEngine::loadSound(SoundInfo & soundInfo)
        {
            if (!soundLoaded(soundInfo)) {
                //::cout << "Audio Engine: Loading Sound from file " << soundInfo.getFilePath() << '\n';
                FMOD::Sound* sound;
                ERRCHECK(lowLevelSystem->createSound(soundInfo.getFilePath_inChar(), soundInfo.is3D ? FMOD_3D : FMOD_2D, 0, &sound));
                ERRCHECK(sound->setMode(soundInfo.isLoop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF));
                ERRCHECK(sound->set3DMinMaxDistance(0.5f * DISTANCEFACTOR, 5000.0f * DISTANCEFACTOR));
                sounds.insert({ soundInfo.getUniqueID(), sound });
                unsigned int msLength = 0;
                ERRCHECK(sounds[soundInfo.getUniqueID()]->getLength(&msLength, FMOD_TIMEUNIT_MS));
                //soundInfo.setMSLength(msLength);
                soundInfo.whatState = SOUND_LOADED;
            }
            else
                std::cout << "Audio Engine: Sound File was already loaded!\n";
        }

        int AudioEngine::playSound(SoundInfo & soundInfo)
        {
            if (soundLoaded(soundInfo)) {
                if(!soundIsPlaying(soundInfo))
                {
                    if (soundIsPaused(soundInfo))
                    {
                        //std::cout << "Playing Sound\n";
                        FMOD::Channel* channel{ nullptr };
                        // start play in 'paused' state
                        ERRCHECK(lowLevelSystem->playSound(sounds[soundInfo.getUniqueID()], 0, true /* start paused */, &channel));

                        if (soundInfo.is3D)
                            set3dChannelPosition(soundInfo, channel);

                        //std::cout << "Playing sound at volume " << soundInfo.getVolume() << '\n';
                        channel->setVolume(soundInfo.getVolume());

                        if (soundInfo.isLoop) // add to channel map of sounds currently playing, to stop later
                        {
                            loopsPlaying[soundInfo.getUniqueID()] = channel;
                        }
                        else
                        {
                            normalPlaying[soundInfo.getUniqueID()] = channel;
                        }

                        ERRCHECK(channel->setReverbProperties(0, soundInfo.getReverbAmount()));

                        // start audio playback
                        ERRCHECK(channel->setPaused(false));
                    }
                    else
                    {
                        if (soundInfo.isLoop)
                        {
                            ERRCHECK(loopsPlaying[soundInfo.getUniqueID()]->setPaused(false));
                        }
                        else
                        {
                            ERRCHECK(normalPlaying[soundInfo.getUniqueID()]->setPaused(false));
                        }
                    }
                }
                else
                {
                    //std::cout << "Sound is already playing!" << std::endl;
                }
            }
            else
            {
                //std::cout << "Sound not loaded, loading in now." << std::endl;
                loadSound(soundInfo);
                return playSound(soundInfo);
            }

        }

        void AudioEngine::playAllPaused()
        {
            bool check{ false };
            
            for (std::pair<unsigned int, FMOD::Channel*> it : loopsPlaying)
            {
                it.second->getPaused(&check);
                if (check)
                {
                    it.second->setPaused(false);
                }
            }
            for (std::pair<unsigned int, FMOD::Channel*> it : normalPlaying)
            {
                it.second->getPaused(&check);
                if (check)
                {
                    it.second->setPaused(false);
                }
            }
        }

        void AudioEngine::pauseSound(SoundInfo& soundInfo)
        {
            if (soundIsPlaying(soundInfo))
            {
                if (soundInfo.isLoop)
                {
                    ERRCHECK(loopsPlaying[soundInfo.getUniqueID()]->setPaused(true));
                }
                else
                {
                    ERRCHECK(normalPlaying[soundInfo.getUniqueID()]->setPaused(true));
                }
            }
            else
            {
                //std::cout << "Nothing is playing!" << std::endl;
            }
        }

        void AudioEngine::pauseAllSound()
        {
            bool check{ false };

            for (auto ch : normalPlaying)
            {
                ERRCHECK(ch.second->isPlaying(&check));

                if (check)
                {
                    ch.second->setPaused(true);
                }
            }
            for (auto ch : loopsPlaying)
            {
                ERRCHECK(ch.second->isPlaying(&check));

                if (check)
                {
                    ch.second->setPaused(true);
                }
            }
        }

        void AudioEngine::stopSound(SoundInfo & soundInfo)
        {
            if (soundIsPlaying(soundInfo))
            {
                if(soundInfo.isLoop)
                {
                    ERRCHECK(loopsPlaying[soundInfo.getUniqueID()]->stop());
                    //loopsPlaying.erase(soundInfo.getUniqueID());
                    soundInfo.whatState = SOUND_LOADED; //set the sound back to loaded state
                }
                else
                {
                    ERRCHECK(normalPlaying[soundInfo.getUniqueID()]->stop());
                    //normalPlaying.erase(soundInfo.getUniqueID());
                    soundInfo.whatState = SOUND_LOADED;
                }
                //std::cout << "Stopping sound" << std::endl;
            }
            else
            {
                //std::cout << "Audio Engine: Can't stop a looping sound that's not playing!\n";
                //std::cout << "No sound is playing" << std::endl;
            }
        }

        void AudioEngine::stopAllSound()
        {
            bool check{ false };

            for (auto ch : normalPlaying)
            {
                ERRCHECK(ch.second->isPlaying(&check));

                if (check)
                {
                    ch.second->stop();
                }
            }
            for (auto ch : loopsPlaying)
            {
                ERRCHECK(ch.second->isPlaying(&check));

                if (check)
                {
                    ch.second->stop();
                }
            }
        }

        void AudioEngine::FadeOutSound(unsigned int duration, SoundInfo& soundInfo)
        {
            unsigned long long DSPClock{ 0 };
            int rate{ 0 };
            ERRCHECK(lowLevelSystem->getSoftwareFormat(&rate, 0, 0));
            
            if (soundInfo.isLoop)
            {
                ERRCHECK(loopsPlaying[soundInfo.uniqueID]->getDSPClock(0, &DSPClock));
                ERRCHECK(loopsPlaying[soundInfo.uniqueID]->addFadePoint(DSPClock, soundInfo.volume));
                ERRCHECK(loopsPlaying[soundInfo.uniqueID]->addFadePoint(DSPClock + (rate * duration), 0.f));
                ERRCHECK(loopsPlaying[soundInfo.uniqueID]->setDelay(0, DSPClock + (rate * duration), true));
            }
            else
            {
                ERRCHECK(normalPlaying[soundInfo.uniqueID]->getDSPClock(0, &DSPClock));
                ERRCHECK(normalPlaying[soundInfo.uniqueID]->addFadePoint(DSPClock, soundInfo.volume));
                ERRCHECK(normalPlaying[soundInfo.uniqueID]->addFadePoint(DSPClock + (rate * duration), 0.f));
                ERRCHECK(normalPlaying[soundInfo.uniqueID]->setDelay(0, DSPClock + (rate * duration), true));
            }
        }

        void AudioEngine::FadeInSound(unsigned int duration, SoundInfo& soundInfo)
        {
            pauseSound(soundInfo);

            unsigned long long DSPClock{ 0 };
            int rate{ 0 };
            ERRCHECK(lowLevelSystem->getSoftwareFormat(&rate, 0, 0));

            if (soundInfo.isLoop)
            {
                ERRCHECK(loopsPlaying[soundInfo.uniqueID]->getDSPClock(0, &DSPClock));
                ERRCHECK(loopsPlaying[soundInfo.uniqueID]->addFadePoint(DSPClock, 0.f));
                ERRCHECK(loopsPlaying[soundInfo.uniqueID]->addFadePoint(DSPClock + (rate * duration), soundInfo.volume));
            }
            else
            {
                ERRCHECK(normalPlaying[soundInfo.uniqueID]->getDSPClock(0, &DSPClock));
                ERRCHECK(normalPlaying[soundInfo.uniqueID]->addFadePoint(DSPClock, 0.f));
                ERRCHECK(normalPlaying[soundInfo.uniqueID]->addFadePoint(DSPClock + (rate * duration), soundInfo.volume));
            }
        }

        void AudioEngine::updateSoundLoopVolume(SoundInfo & soundInfo, float newVolume, unsigned int fadeSampleLength)
        {
            if (soundIsPlaying(soundInfo)) {
                FMOD::Channel* channel = loopsPlaying[soundInfo.getUniqueID()];
                if (fadeSampleLength <= 64) // 64 samples is default volume fade out
                    ERRCHECK(channel->setVolume(newVolume));
                else {
                    bool fadeUp = newVolume > soundInfo.getVolume();
                    // get current audio clock time
                    unsigned long long parentclock = 0;
                    ERRCHECK(channel->getDSPClock(NULL, &parentclock));

                    float targetFadeVol = fadeUp ? 1.0f : newVolume;

                    if (fadeUp) ERRCHECK(channel->setVolume(newVolume));

                    ERRCHECK(channel->addFadePoint(parentclock, soundInfo.getVolume()));
                    ERRCHECK(channel->addFadePoint(parentclock + fadeSampleLength, targetFadeVol));
                    //std::cout << "Current DSP Clock: " << parentclock << ", fade length in samples  = " << fadeSampleLength << "\n";
                }
                //std::cout << "Updating with new soundinfo vol \n";
                soundInfo.setVolume(newVolume); // update the SoundInfo's volume
            }
            else
                std::cout << "AudioEngine: Can't update sound loop volume! (It isn't playing or might not be loaded)\n";
        }


        void AudioEngine::update3DSoundPosition(SoundInfo& soundInfo)
        {
            if (soundIsPlaying(soundInfo))
                set3dChannelPosition(soundInfo, loopsPlaying[soundInfo.getUniqueID()]);
            else
                std::cout << "Audio Engine: Can't update sound position!\n";

        }

        bool AudioEngine::soundIsPlaying(SoundInfo& soundInfo)
        {
            int channelnum{ 0 };

            ERRCHECK(lowLevelSystem->getChannelsPlaying(&channelnum));

            if (soundIsPlaying(soundInfo) && channelnum <= MAX_AUDIO_CHANNELS)
            {
                return true;
            }

            return false;
        }

        bool AudioEngine::soundIsPaused(SoundInfo& soundInfo)
        {
            bool check{ false };

            if (soundInfo.isLoop)
            {
                loopsPlaying[soundInfo.getUniqueID()]->getPaused(&check);
            }
            else
            {
                normalPlaying[soundInfo.getUniqueID()]->getPaused(&check);
            }

            return check;
        }

        bool AudioEngine::soundFinished(SoundInfo& soundInfo)
        {
            bool check{ false };

            if (soundInfo.isLoop)
            {
                loopsPlaying[soundInfo.getUniqueID()]->isPlaying(&check);
            }
            else
            {
                normalPlaying[soundInfo.getUniqueID()]->isPlaying(&check);
            }

            if (!check)
            {
                soundInfo.whatState = SOUND_LOADED;
            }

            return !check;
        }

        void AudioEngine::set3DListenerPosition(float posX, float posY, float posZ, float forwardX, float forwardY, float forwardZ, float upX, float upY, float upZ)
        {
            listenerpos = { posX,     posY,     posZ };
            forward = { forwardX, forwardY, forwardZ };
            up = { upX,      upY,      upZ };
            ERRCHECK(lowLevelSystem->set3DListenerAttributes(0, &listenerpos, 0, &forward, &up));
        }

        unsigned int AudioEngine::getSoundLengthInMS(SoundInfo soundInfo)
        {
            unsigned int length = 0;
            if (sounds.count(soundInfo.getUniqueID()))
                ERRCHECK(sounds[soundInfo.getUniqueID()]->getLength(&length, FMOD_TIMEUNIT_MS));
            return length;
        }

        void AudioEngine::loadFMODStudioBank(const char* filepath)
        {
            //std::cout << "Audio Engine: Loading FMOD Studio Sound Bank " << filepath << '\n';
            FMOD::Studio::Bank* bank = NULL;
            ERRCHECK(studioSystem->loadBankFile(filepath, FMOD_STUDIO_LOAD_BANK_NORMAL, &bank));
            soundBanks.insert({ filepath, bank });
        }

        void AudioEngine::loadFMODStudioEvent(const char* eventName, std::vector<std::pair<const char*, float>> paramsValues)
        { //std::vector<std::map<const char*, float>> perInstanceParameterValues) {
            //std::cout << "AudioEngine: Loading FMOD Studio Event " << eventName << '\n';
            FMOD::Studio::EventDescription* eventDescription = NULL;
            ERRCHECK(studioSystem->getEvent(eventName, &eventDescription));
            // Create an instance of the event
            FMOD::Studio::EventInstance* eventInstance = NULL;
            ERRCHECK(eventDescription->createInstance(&eventInstance));
            for (const auto& parVal : paramsValues) {
                //std::cout << "AudioEngine: Setting Event Instance Parameter " << parVal.first << "to value: " << parVal.second << '\n';
                // Set the parameter values of the event instance
                ERRCHECK(eventInstance->setParameterByName(parVal.first, parVal.second));
            }
            eventInstances.insert({ eventName, eventInstance });
            eventDescriptions.insert({ eventName, eventDescription });
        }

        void AudioEngine::setFMODEventParamValue(const char* eventName, const char* parameterName, float value)
        {
            if (eventInstances.count(eventName) > 0)
                ERRCHECK(eventInstances[eventName]->setParameterByName(parameterName, value));
            else
                std::cout << "AudioEngine: Event " << eventName << " was not in event instance cache, can't set param \n";

        }

        void AudioEngine::playEvent(const char* eventName, int instanceIndex)
        {
            (void)instanceIndex;//TODO
            printEventInfo(eventDescriptions[eventName]);
            //auto eventInstance = eventInstances[eventName];
            if (eventInstances.count(eventName) > 0)
                ERRCHECK(eventInstances[eventName]->start());
            else
                std::cout << "AudioEngine: Event " << eventName << " was not in event instance cache, cannot play \n";
        }

        void AudioEngine::stopEvent(const char* eventName, int instanceIndex)
        {
            (void)instanceIndex;//TODO
            if (eventInstances.count(eventName) > 0)
                ERRCHECK(eventInstances[eventName]->stop(FMOD_STUDIO_STOP_ALLOWFADEOUT));
            else
                std::cout << "AudioEngine: Event " << eventName << " was not in event instance cache, cannot stop \n";
        }

        void AudioEngine::setEventVolume(const char* eventName, float volume0to1)
        {
            //std::cout << "AudioEngine: Setting Event Volume\n";
            ERRCHECK(eventInstances[eventName]->setVolume(volume0to1));
        }

        bool AudioEngine::eventIsPlaying(const char* eventName, int instance /*= 0*/)
        {
            (void)instance;
            FMOD_STUDIO_PLAYBACK_STATE playbackState;
            ERRCHECK(eventInstances[eventName]->getPlaybackState(&playbackState));
            return playbackState == FMOD_STUDIO_PLAYBACK_PLAYING;
        }

        void AudioEngine::mute(SoundInfo& soundInfo)
        {
            if (soundIsPlaying(soundInfo))
            {
                if (soundInfo.isLoop)
                {
                    ERRCHECK(loopsPlaying[soundInfo.getUniqueID()]->setMute(true));
                }
                else
                {
                    ERRCHECK(normalPlaying[soundInfo.getUniqueID()]->setMute(true));
                }

                soundInfo.isMuted = true;
            }
        }

        void AudioEngine::unmute(SoundInfo& soundInfo)
        {
            if (soundInfo.isMuted)
            {
                if (soundInfo.isLoop)
                {
                    ERRCHECK(loopsPlaying[soundInfo.getUniqueID()]->setMute(false));
                }
                else
                {
                    ERRCHECK(normalPlaying[soundInfo.getUniqueID()]->setMute(false));
                }

                soundInfo.isMuted = false;
            }
        }

        void AudioEngine::muteAllSounds()
        {
            ERRCHECK(mastergroup->setMute(true));
            muted = true;
        }

        void AudioEngine::unmuteAllSound()
{
            ERRCHECK(mastergroup->setMute(false));
            muted = false;
        }

        bool AudioEngine::isMuted()
        {
            return muted;
        }

        std::map<unsigned int, FMOD::Sound*> AudioEngine::getSoundContainer()
        {
            return sounds;
        }

        std::map<std::string, FMOD::Studio::Bank*> AudioEngine::getBankContainer()
        {
            return soundBanks;
        }

        std::map<std::string, FMOD::Studio::EventDescription*> AudioEngine::getEventDescriptionContainer()
        {
            return eventDescriptions;
        }

        std::map<std::string, FMOD::Studio::EventInstance*> AudioEngine::getEventInstanceContainer()
        {
            return eventInstances;
        }

        //// Private definitions 
        bool AudioEngine::soundLoaded(SoundInfo soundInfo)
        {
            //std::cout << "Checking sound " << soundInfo.getUniqueID() << " exists\n";
            return (sounds.count(soundInfo.getUniqueID()) > 0);
        }

        void AudioEngine::set3dChannelPosition(SoundInfo soundInfo, FMOD::Channel * channel)
        {
            FMOD_VECTOR position = { soundInfo.getX() * DISTANCEFACTOR, soundInfo.getY() * DISTANCEFACTOR, soundInfo.getZ() * DISTANCEFACTOR };
            FMOD_VECTOR velocity = { 0.0f, 0.0f, 0.0f }; // TODO Add dopplar (velocity) support
            ERRCHECK(channel->set3DAttributes(&position, &velocity));
        }

        void AudioEngine::initReverb()
        {
            ERRCHECK(lowLevelSystem->createReverb3D(&reverb));
            FMOD_REVERB_PROPERTIES prop2 = FMOD_PRESET_CONCERTHALL;
            ERRCHECK(reverb->setProperties(&prop2));
            ERRCHECK(reverb->set3DAttributes(&revPos, revMinDist, revMaxDist));
        }

        // Error checking/debugging function definitions

        void ERRCHECK_fn(FMOD_RESULT result, const char* file, int line)
        {
            (void)file;//TODO
            if (result != FMOD_OK)
                std::cout << "FMOD ERROR: AudioEngine.cpp [Line " << line << "] " << result << "  - " << FMOD_ErrorString(result) << '\n';
        }

        void AudioEngine::printEventInfo(FMOD::Studio::EventDescription * eventDescription)
        {

            int params;
            bool is3D, isOneshot;
            ERRCHECK(eventDescription->getParameterDescriptionCount(&params));
            ERRCHECK(eventDescription->is3D(&is3D));
            ERRCHECK(eventDescription->isOneshot(&isOneshot));

            std::cout << "FMOD EventDescription has " << params << " parameter descriptions, "
                << (is3D ? " is " : " isn't ") << " 3D, "
                << (isOneshot ? " is " : " isn't ") << " oneshot, "
                << (eventDescription->isValid() ? " is " : " isn't ") << " valid."
                << '\n';
        }
    } //end of AudioWerks

    AudioWerks::AudioEngine* proxy_audio_system::aud_instance = nullptr;
    int proxy_audio_system::totalNumClips{ 0 };
    bool proxy_audio_system::Q_state{ false };
    SoundInfo proxy_audio_system::Q_name{};

    std::map<std::string, SoundInfo> proxy_audio_system::allSounds;
    std::map<std::string, std::pair<bool, SoundInfo*>> proxy_audio_system::Queue;
    //std::map<unsigned int, std::map<Vec3*, SOUND_STATE*>> sound_events{};

    void proxy_audio_system::audio_system_init()
    {
        aud_instance = AudioWerks::AudioEngine::get_audioengine_instance();
        totalNumClips = aud_instance->getSoundContainer().size();

        allSounds.clear();
        Queue.clear();

        load_all_audio_files();
    }

    void proxy_audio_system::audio_system_update(const float dt, const std::vector<EntityID>& entities, Transform* soundInfo)
    {
        aud_instance->update();
    }

    void proxy_audio_system::audio_event_init(SoundInfo* container)
    {
        //sound_events[container->getUniqueID()] = container->getEvents();
    }

    void proxy_audio_system::audio_event_update()
    {
        
    }

    void proxy_audio_system::load_all_audio_files()
    {
        std::filesystem::path full_path = "../assets/audioFiles/"; //pathing / append
        std::vector<std::filesystem::path> all_files; //store all file path

        if (std::filesystem::is_directory(full_path))
        {
            all_files = go_deeper(full_path);
        }

        for (auto& str : all_files)
        {
            if (str.string().find(".txt") == std::string::npos && str.string().find(".meta") == std::string::npos)
            {
                SoundInfo temp(str.string());
                size_t first = str.string().find_last_of('\\') + 1,
                    last = str.string().find_last_of('.') - first;
                std::string sound_name = str.string().substr(first, last);

                allSounds[sound_name] = (temp);
                aud_instance->loadSound(temp);
            }
        }
    }

    std::vector<std::filesystem::path> proxy_audio_system::go_deeper(std::filesystem::path f_path)
    {
        std::vector<std::filesystem::path> folders;
        std::vector<std::filesystem::path> files;

        for (auto& temp : std::filesystem::directory_iterator(f_path))
        {
            if (temp.is_directory())
            {
                folders = go_deeper(temp);

                for (auto& temp2 : folders)
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

    void proxy_audio_system::ScriptPlay(std::string pathing)
    {
        for (auto& temp : allSounds)
        {
            if(strstr(temp.first.c_str(), pathing.c_str()))
            {
                aud_instance->playSound(temp.second);
                break;
            }
        }
    }

    void proxy_audio_system::ScriptPause(std::string pathing)
    {
        for (auto& temp : allSounds)
        {
            if (strstr(temp.first.c_str(), pathing.c_str()))
            {
                aud_instance->pauseSound(temp.second);
            }
        }
    }

    void proxy_audio_system::ScriptStop(std::string pathing)
    {
        for (auto& temp : allSounds)
        {
            if (strstr(temp.first.c_str(), pathing.c_str()))
            {
                aud_instance->stopSound(temp.second);
            }
        }
    }

    void proxy_audio_system::ScriptPlayAllPaused()
    {
        aud_instance->playAllPaused();
    }

    void proxy_audio_system::ScriptPauseAll()
    {
        aud_instance->pauseAllSound();
    }

    void proxy_audio_system::ScriptStopAll()
    {
        for (auto& temp : allSounds)
        {
            aud_instance->stopSound(temp.second);
        }
    }

    bool proxy_audio_system::ScriptAnySoundPlaying()
    {
        return aud_instance->anySoundPlaying();
    }

    void proxy_audio_system::ScriptFadeOut(unsigned int duration, std::string pathing)
    {
        if (allSounds.find(pathing) != allSounds.end())
        {
            aud_instance->FadeOutSound(duration, allSounds[pathing]);
        }
    }

    void proxy_audio_system::ScriptFadeIn(unsigned int duration, std::string pathing)
    {
        if (allSounds.find(pathing) != allSounds.end())
        {
            aud_instance->FadeInSound(duration, allSounds[pathing]);
        }
    }

    SoundInfo* proxy_audio_system::find_sound_info(std::string str)
    {
        for (auto& temp : allSounds)
        {
            if (temp.first == str)
            {
                return &temp.second;
            }
        }

        return nullptr;
    }

    void proxy_audio_system::Add_to_Queue(std::string str)
    {
        Queue[str] = std::make_pair(true, find_sound_info(str));
    }

    void proxy_audio_system::Remove_from_Queue(std::string str)
    {
        Queue.erase(str);
    }

    void proxy_audio_system::Play_queue()
    {        
        /*Q_state = true;

        if (Queue.begin()->second.first)
        {
            aud_instance->playSound(*Queue.begin()->second.second);
            Q_name = *Queue.begin()->second.second;
            Queue.extract(Queue.begin()->first);
        }
        if (aud_instance->soundIsPlaying(Q_name))
        {
            Q_name = Queue.begin()->first;
        }
        if (Queue.empty())
        {
            Q_state = false;
        }*/
    }

    void proxy_audio_system::Clear_queue()
    {
        Queue.clear();
    }

    bool proxy_audio_system::checkifdone(std::string str)
    {
        bool check{ false };

        for (auto& temp : allSounds)
        {
            if (strstr(temp.first.c_str(), str.c_str()))
            {
                check = aud_instance->soundFinished(temp.second);
            }
        }

        return check;
    }
    
    /*void proxy_audio_system::audio_event_play(SoundInfo& soundInfo)
    {
        aud_instance->playSound(soundInfo);
    }*/
} //end of TDS