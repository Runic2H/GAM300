#ifndef SOUND
#define SOUND

#include <string>
#include <array>
#include <time.h>

#include "components/iComponent.h"
#include "Vector3.h"
#include "ecs/ecs.h"

namespace TDS
{

    static unsigned int ID_Count{ 0 };

    /*enum SOUND_STATE : uint16_t
    {
        SOUND_LOADED = 0,
        SOUND_PLAYING,
        SOUND_STOP,
        SOUND_MUTED
    };*/

    enum SOUND_STATE
    {
        SOUND_ERR = 0,
        SOUND_LOADED,
        SOUND_PLAYING,
        SOUND_PAUSE
    };

    namespace AudioWerls
    {
        class AudioEngine;
    }

    DLL_API struct SoundInfo : public IComponent
    {
        unsigned int uniqueID, MSLength;
        std::string filePath;
        bool isitLoop, isit3D, isitmuted;
        SOUND_STATE whatState;
        Vec3 position;
        float volume, ReverbAmount;
        std::map<Vec3*, SOUND_STATE*> position_events;

        /**
         * @brief Loading info from a file into SOUNDINFO.
         * @param obj
         * @return true when success.
        */
        //virtual bool Deserialize(const rapidjson::Value& obj)
        //{
        //    position = { obj["PositionX"].GetFloat(), obj["PositionY"].GetFloat(), obj["PositionZ"].GetFloat() };
        //    filePath = { obj["file"].GetString() };
        //    isitLoop = { obj["Loop"].GetBool() };
        //    isit3D = { obj["3D"].GetBool() };
        //    

        //    return true; //Change this to return based of whether it's really successful or not
        //}

        ///**
        // * @brief Storing info from SOUNDINFO into a file
        // * @param writer 
        // * @return true when success.
        //*/
        //virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
        //{
        //    writer->Key("PositionX");
        //    writer->Double(static_cast<float>(position[0]));

        //    return true; //Change this to return based of whether it's really successful or not
        //}

        // convenience method to set the 3D coordinates of the sound.
        DLL_API  void set3DCoords(float x, float y, float z);

        DLL_API  void set3DCoords(Vec3 set_this);

        DLL_API  void setFilePath(std::string _path);

        DLL_API  void setEvents(Vec3* place, SOUND_STATE& type);

        DLL_API  bool isLoaded();

        DLL_API  bool is3D();

        DLL_API  bool isLoop();

        DLL_API  bool isMuted();

        DLL_API  bool isPlaying();

        DLL_API  bool isPaused();

        /*bool isPlaying()
        {
            return (bool)(whatState & (1 << SOUND_PLAYING));
        }

        bool isPaused()
        {
            return (bool)(whatState ^ (1 << SOUND_PLAYING));
        }

        bool isMuted()
        {
            return (bool)(whatState & (1 << SOUND_MUTED));
        }*/

        DLL_API  Vec3 get3DCoords();

        DLL_API  std::map<Vec3*, SOUND_STATE*> getEvents();

        DLL_API  SOUND_STATE getState();

        DLL_API  unsigned int getUniqueID();

        DLL_API  unsigned int getMSLength();

        DLL_API  std::string getFilePath();

        DLL_API  const char* getFilePath_inChar();

        DLL_API  float getX();

        DLL_API  float getY();

        DLL_API  float getZ();

        DLL_API  float getReverbAmount();

        DLL_API  float getVolume();

        /**
        * Parameter takes in Volume values (0 - 100)
        */
        DLL_API  void setVolume(float vol);

        DLL_API  void setMSLength(unsigned int len);

        /*void setState(SOUND_STATE setting, bool set)
        {
            whatState |= (set << setting);
        }*/

        DLL_API  void setState(SOUND_STATE setting);

        DLL_API  void setLoop(bool condition);

        DLL_API  void set3D(bool condition);

        DLL_API  void setMute(bool condition);

        DLL_API  void setReverbAmount(float reverb);

        DLL_API  void play();
        DLL_API  void pause();
        DLL_API  void stop();

        DLL_API  SoundInfo(std::string _filePath = "", bool _isLoop = false, bool _is3D = false, bool _muted = false, SOUND_STATE _theState = SOUND_ERR, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _volume = 1.f, float _reverbamount = 0.f);

        // TODO  implement sound instancing
        // int instanceID = -1; 
        void operator=(const SoundInfo& rhs)
        {
            uniqueID = rhs.uniqueID;
            MSLength = rhs.MSLength;
            filePath = rhs.filePath;
            isitLoop = rhs.isitLoop;
            isit3D = rhs.isit3D;
            isitmuted = rhs.isitmuted;
            whatState = rhs.whatState;
            position = rhs.position;
            volume = rhs.volume;
            ReverbAmount = rhs.ReverbAmount;
        }
        RTTR_ENABLE(IComponent);
        RTTR_REGISTRATION_FRIEND

    }; //end of SoundInfo struct

    DLL_API  SoundInfo* GetSoundInfo(EntityID ID);

} //end of namespace TDS

#endif