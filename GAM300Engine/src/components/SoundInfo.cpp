#include "components/SoundInfo.h"
#include "fmod_engine/AudioEngine.h"

RTTR_REGISTRATION
{
    using namespace TDS;

rttr::registration::class_<SoundInfo>("Audio")
.property("File path", &SoundInfo::filePath)
.property("Loop", &SoundInfo::isitLoop)
.property("3D", &SoundInfo::isit3D)
.property("Muted", &SoundInfo::isitmuted)
.property("Position", &SoundInfo::position)
.property("volume", &SoundInfo::volume)
.property("Reverb", &SoundInfo::ReverbAmount)
.property("MS Length", &SoundInfo::MSLength)

.method("set3DCoords", rttr::select_overload<void(float, float, float)>(&SoundInfo::set3DCoords))
.method("set3DCoords", rttr::select_overload<void(Vec3)>(&SoundInfo::set3DCoords))
.method("setFilePath", &SoundInfo::setFilePath)
.method("setEvents", &SoundInfo::setEvents)
.method("isLoaded", &SoundInfo::isLoaded)
.method("is3D", &SoundInfo::is3D)
.method("play", &SoundInfo::play)
.method("pause", &SoundInfo::pause)
.method("stop", &SoundInfo::stop);
}

namespace TDS
{
    void SoundInfo::set3DCoords(float x, float y, float z)
    {
        position.x = x;
        position.y = y;
        position.z = z;
    }

    void SoundInfo::set3DCoords(Vec3 set_this)
    {
        position = set_this;
    }

    void SoundInfo::setFilePath(std::string _path)
    {
        filePath = _path;
    }

    void SoundInfo::setEvents(Vec3* place, SOUND_STATE& type)
    {
        position_events[place] = &type;
    }

    bool SoundInfo::isLoaded()
    {
        return (whatState == SOUND_LOADED);
    }

    bool SoundInfo::is3D()
    {
        return isit3D;
    }

    bool SoundInfo::isLoop()
    {
        return isitLoop;
    }

    bool SoundInfo::isMuted()
    {
        return isitmuted;
    }

    bool SoundInfo::isPlaying()
    {
        return (whatState == SOUND_PLAYING);
    }

    bool SoundInfo::isPaused()
    {
        return (whatState == SOUND_PAUSE);
    }

    Vec3 SoundInfo::get3DCoords()
    {
        return position;
    }

    std::map<Vec3*, SOUND_STATE*> SoundInfo::getEvents()
    {
        return position_events;
    }

    SOUND_STATE SoundInfo::getState()
    {
        return whatState;
    }

    unsigned int SoundInfo::getUniqueID()
    {
        return uniqueID;
    }

    unsigned int SoundInfo::getMSLength()
    {
        return MSLength;
    }

    std::string SoundInfo::getFilePath()
    {
        return filePath;
    }

    const char* SoundInfo::getFilePath_inChar()
    {
        const char* name = filePath.c_str();

        return name;
    }

    float SoundInfo::getX()
    {
        return position[0]; //!!!!!!!To be replaced when vec container is used
    }

    float SoundInfo::getY()
    {
        return position[1]; //!!!!!!!To be replaced when vec container is used
    }

    float SoundInfo::getZ()
    {
        return position[2]; //!!!!!!!To be replaced when vec container is used
    }

    float SoundInfo::getReverbAmount()
    {
        return ReverbAmount;
    }

    float SoundInfo::getVolume()
    {
        return volume;
    }

    /**
    * Parameter takes in Volume values (0 - 100)
    */
    void SoundInfo::setVolume(float vol)
    {
        volume = 20.0f * log10f(vol);

        if (volume > 1.f)
        {
            volume = 1.f;
        }
    }

    void SoundInfo::setMSLength(unsigned int len)
    {
        MSLength = len;
    }

    void SoundInfo::setState(SOUND_STATE setting)
    {
        whatState = setting;
    }

    void SoundInfo::setLoop(bool condition)
    {
        isitLoop = condition;
    }

    void SoundInfo::set3D(bool condition)
    {
        isit3D = condition;
    }

    void SoundInfo::setMute(bool condition)
    {
        isitmuted = condition;
    }

    void SoundInfo::setReverbAmount(float reverb)
    {
        ReverbAmount = reverb;
    }

    void SoundInfo::play()
    {
        AudioWerks::AudioEngine* audeng = AudioWerks::AudioEngine::get_audioengine_instance();
        audeng->playSound(*this);
    }
    void SoundInfo::pause()
    {
        AudioWerks::AudioEngine* audeng = AudioWerks::AudioEngine::get_audioengine_instance();
        audeng->pauseSound(*this);
    }
    void SoundInfo::stop()
    {
        AudioWerks::AudioEngine* audeng = AudioWerks::AudioEngine::get_audioengine_instance();
        audeng->stopSound(*this);
    }

    SoundInfo::SoundInfo(std::string _filePath, bool _isLoop, bool _is3D, bool _muted, SOUND_STATE _theState, float _x, float _y, float _z, float _volume, float _reverbamount)
        : filePath(_filePath), isitLoop(_isLoop), isit3D(_is3D), isitmuted(_muted), whatState(_theState), volume(_volume), ReverbAmount(_reverbamount)
    {
        position.x = _x;
        position.y = _y;
        position.z = _z;
        position_events.clear();
        MSLength = 0;
        uniqueID = ID_Count++; //Change UID to include time when added
    }

    SoundInfo* GetSoundInfo(EntityID ID)
    {
        return ecs.getComponent<SoundInfo>(ID);
    }
}