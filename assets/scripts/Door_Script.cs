using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;
using UnityEngine.UI;

public class Door_Script : MonoBehaviour
{
    public GameObject _InteractUI;
    public Animator doorAnimator;
    public GameObject lockpick;
    public LockPick1 lockpickScript;
    public float doorState = 0; //0 is closed, 1 is open
    public bool locked = true;
    public bool forcedLocked;
    public bool chainedShut;
    public AudioClip[] _DoorSounds;
    public AudioSource _DoorAudioSource;
    public bool collided;

    [Header("VO Variables")]
    public Text mySubtitles;
    public string[] myVOTexts;
    public AudioClip[] forceLocked_VOLines;
    public AudioSource voSource;
    int forcelockedAudioCount = -1;
    bool playForcedLockedAudio;

    // Update is called once per frame
    void Update()
    {
        if (collided)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                if (!locked)
                {
                    Open_CloseFunction();
                    _InteractUI.SetActive(true);
                }
                else if (chainedShut)
                {

                }
                else if (forcedLocked)
                {
                    playForcedLockedAudio = true;
                    forcelockedAudioCount = -1;
                }
                else if (!lockpick.gameObject.activeInHierarchy && !forcedLocked)
                {
                    _InteractUI.SetActive(false);
                    lockpick.SetActive(true);
                    lockpickScript.newLock();
                }
            }

            if (lockpickScript.unlocked)
            {
                lockpickScript.unlocked = false;
                lockpick.SetActive(false);
                locked = false;
                _InteractUI.SetActive(true);
            }
        }

        if (playForcedLockedAudio)
        {
            PlayVO();
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.name == "Enemy")
        {
            Open_CloseFunction();
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.name == "Enemy")
        {
            Open_CloseFunction();
        }
    }

    public void Open_CloseFunction()
    {
        if (doorState == 0)
        {
            doorAnimator.SetBool("Open", true);
            doorState = 1;
        }
        else
        {
            doorAnimator.SetBool("Open", false);
            doorState = 0;
        }
    }

    public void PlayVO()
    {
        bool changedAudio = false;

        if (!voSource.isPlaying)
        {
            if (!changedAudio && forcelockedAudioCount < 2)
            {
                //select audio clip
                voSource.clip = forceLocked_VOLines[forcelockedAudioCount += 1];
                voSource.Play();

                //select subtitle
                mySubtitles.enabled = true;
                mySubtitles.text = myVOTexts[forcelockedAudioCount];
                changedAudio = true;
            }
            else
            {
                mySubtitles.enabled = false;
            }
        }
        else if (voSource.isPlaying)
        {
            changedAudio = false;
        }
    }
}
