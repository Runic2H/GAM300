#ifndef SOUND
#define SOUND

#include <string>
#include <array>
#include <time.h>

namespace TDS{
    static unsigned int counter{ 0 };

    enum SOUND_STATE
    {
        SOUND_ERR = 0,
        SOUND_LOADED,
        SOUND_UNLOAD,
        SOUND_PLAYING
    };

    struct SoundInfo
    {

        unsigned int uniqueID, MSLength;
        const char* filePath;
        bool isitLoop, isit3D;
        SOUND_STATE whatState;
        std::array<float, 3> posVec; //!!!!!!!To be replaced when vec container is used
        float volume, ReverbAmount;

        // convenience method to set the 3D coordinates of the sound.
        void set3DCoords(float x, float y, float z) {
            this->posVec[0] = x, this->posVec[1] = y, this->posVec[2] = z; //!!!!!!!To be replaced when vec container is used
        }

        bool isLoaded()
        {
            return (whatState == SOUND_LOADED);
        }

        bool is3D()
        {
            return isit3D;
        }

        bool isLoop()
        {
            return isitLoop;
        }

        bool isPlaying()
        {
            return (whatState == SOUND_PLAYING);
        }

        unsigned int getUniqueID()
        {
            return uniqueID;
        }

        const char* getFilePath()
        {
            return filePath;
        }

        float getX()
        {
            return posVec[0]; //!!!!!!!To be replaced when vec container is used
        }

        float getY()
        {
            return posVec[1]; //!!!!!!!To be replaced when vec container is used
        }

        float getZ()
        {
            return posVec[2]; //!!!!!!!To be replaced when vec container is used
        }

        float getReverbAmount()
        {
            return ReverbAmount;
        }

        float getVolume()
        {
            return volume;
        }

        /**
        * Parameter takes in Volume values (0 - 100)
        */
        void setVolume(float vol)
        {
            /*volume = 20.0f * log10f(vol);

            if (volume > 150.f)
            {
                volume = 149.f;
            }*/

            volume = 1.f;
        }

        void setMSLength(unsigned int len)
        {
            MSLength = len;
        }

        void setState(SOUND_STATE setting)
        {
            whatState = setting;
        }

        void setLoop(bool condition)
        {
            isitLoop = condition;
        }

        void set3D(bool condition)
        {
            isit3D = condition;
        }

        SoundInfo(const char* _filePath = "", bool _isLoop = false, bool _is3D = false, SOUND_STATE _theState = SOUND_UNLOAD, float _x = 0.0f, float _y = 0.0f, float _z = 0.0f, float _volume = 50.f, float _reverbamount = 0.f)
            : filePath(_filePath), isitLoop(_isLoop), isit3D(_is3D), whatState(_theState), posVec{ _x, _y, _z }, volume(_volume), ReverbAmount(_reverbamount)  //!!!!!!!To be replaced when vec container is used
        {
            uniqueID = counter++; //Change UID to include time when added
        }

        // TODO  implement sound instancing
        // int instanceID = -1; 

    };
}

#endif