﻿using ScriptAPI;
using System;
using static System.Net.Mime.MediaTypeNames;
using static System.Runtime.CompilerServices.RuntimeHelpers;

public class Door_Script : Script
{
    /*
    //public GameObject _InteractUI;
    //public Animator doorAnimator;
    public GameObject playerCamera;
    public GameObject lockpickGroup;
    //public LockPick1 lockpickScript;
    //public bool doorState = false; //false is closed, true is open
    public bool locked = true;
    //public bool forcedLocked;
    //public bool chainedShut;
    //public AudioClip[] _DoorSounds;
    //public AudioSource _DoorAudioSource;
    //public bool collided;

    //[Header("VO Variables")]
   // public Text mySubtitles;
    //public string[] myVOTexts;
    //public AudioClip[] forceLocked_VOLines;
    //public AudioSource voSource;
    //int forcelockedAudioCount = -1;
    //bool playForcedLockedAudio;
    override public void Awake()
    {
        locked = true;
    }

    // Update is called once per frame
    override public void Update()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsSensorActivated())
        {
            if (Input.GetKeyDown(Keycode.E))
            {
                if (!locked)
                {
                    //Open_CloseFunction();
                    //_InteractUI.SetActive(_InteractUI.GetEntityID(), true);
                }
                else // locked
                {
                    // Turn off player
                    playerCamera.SetActive(playerCamera.GetEntityID(), false);
                    // Turn on lockpick group
                    lockpickGroup.SetActive(lockpickGroup.GetEntityID(), true);
                    GraphicsManagerWrapper.ToggleViewFrom2D(true);
                }
                //else if (chainedShut)
                //{

                //}
                //else if (forcedLocked)
                //{
                //    playForcedLockedAudio = true;
                //    forcelockedAudioCount = -1;
                //}
                //else if (!lockpick.activeInHierarchy(lockpick.GetEntityID()) && !forcedLocked)
                //{
                //    _InteractUI.SetActive(_InteractUI.GetEntityID(), false);
                //    lockpick.SetActive(lockpick.GetEntityID(), true);
                //    lockpickScript.newLock();
                //}
            }

            //if (lockpickScript.unlocked)
            //{
            //    lockpickScript.unlocked = false;
            //    lockpick.SetActive(false);
            //    locked = false;
            //    _InteractUI.SetActive(true);
            //}
        }

        //if (playForcedLockedAudio)
        //{
        //    PlayVO();
        //}
    }

    //private void OnTriggerEnter(Collider other)
    //{
    //    if (other.gameObject.name == "Enemy")
    //    {
    //        Open_CloseFunction();
    //    }
    //}

    //private void OnTriggerExit(Collider other)
    //{
    //    if (other.gameObject.name == "Enemy")
    //    {
    //        Open_CloseFunction();
    //    }
    //}

    //public void Open_CloseFunction()
    //{
    //    if (doorState == 0)
    //    {
    //        doorAnimator.SetBool("Open", true);
    //        doorState = 1;
    //    }
    //    else
    //    {
    //        doorAnimator.SetBool("Open", false);
    //        doorState = 0;
    //    }
    //}

    //public void PlayVO()
    //{
    //    bool changedAudio = false;

    //    if (!voSource.isPlaying)
    //    {
    //        if (!changedAudio && forcelockedAudioCount < 2)
    //        {
    //            //select audio clip
    //            voSource.clip = forceLocked_VOLines[forcelockedAudioCount += 1];
    //            voSource.Play();

    //            //select subtitle
    //            mySubtitles.enabled = true;
    //            mySubtitles.text = myVOTexts[forcelockedAudioCount];
    //            changedAudio = true;
    //        }
    //        else
    //        {
    //            mySubtitles.enabled = false;
    //        }
    //    }
    //    else if (voSource.isPlaying)
    //    {
    //        changedAudio = false;
    //    }
    //}
    */

    public GameObject playerGameObject;
    public CameraComponent playerCamera;
    //public GameObject _InteractUI;
    //public Animator doorAnimator;
    public GameObject lockpickGroup;
    public GameObject lockpick;
    public float doorState = 0; //0 is closed, 1 is open
    public bool locked = true;
    public bool forcedLocked;
    public bool chainedShut;
    //public AudioClip[] _DoorSounds;
    //public AudioSource _DoorAudioSource;
    public bool collided;

    [Header("VO Variables")]
    //public Text mySubtitles;
    //public String[] myVOTexts;
    //public AudioClip[] forceLocked_VOLines;
    //public AudioSource voSource;
    private int forcelockedAudioCount = -1;
    private bool playForcedLockedAudio;

    public GameObject doorStates;
    public int doorIndex;
    public GameObject doorText;

    // Update is called once per frame
    override public void Update()
    {
        if (doorStates.GetComponent<DoorState>().Doors[doorIndex] == DoorState.State.Unlocked)
        {
            doorText.SetActive(false);
            //gameObject.SetActive(false);
            // Door animation here
        }
        else if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            doorText.SetActive(true);
            if (Input.GetKeyDown(Keycode.E))
            {
                lockpickGroup.SetActive(true);
                lockpick.GetComponent<LockPick1>().doorIndex = doorIndex;
                playerGameObject.SetActive(false);
                GraphicsManagerWrapper.ToggleViewFrom2D(true);
            }
        }
        else
        {
            doorText.SetActive(false);
        }

        //if (collided)
        //{
        //    if (Input.GetKeyDown(Keycode.E))
        //    {
        //        if (!locked)
        //        {
        //            Open_CloseFunction();
        //            _InteractUI.SetActive(true);
        //        }
        //        else if (chainedShut)
        //        {

        //        }
        //        else if (forcedLocked)
        //        {
        //            playForcedLockedAudio = true;
        //            forcelockedAudioCount = -1;
        //        }
        //        else if (!lockpick.ActiveInHierarchy() && !forcedLocked)
        //        {
        //            _InteractUI.SetActive(false);
        //            lockpick.SetActive(true);
        //            lockpickScript.newLock();
        //        }
        //    }

        //    if (lockpickScript.unlocked)
        //    {
        //        lockpickScript.unlocked = false;
        //        lockpick.SetActive(false);
        //        locked = false;
        //        _InteractUI.SetActive(true);
        //    }
        //}

        if (playForcedLockedAudio)
        {
            PlayVO();
        }
    }

    override public void OnTriggerEnter(ColliderComponent other)
    {
        if (other.gameObject.GetComponent<NameTagComponent>().GetName() == "Enemy")
        {
            Open_CloseFunction();
        }
    }

    override public void OnTriggerExit(ColliderComponent other)
    {
        if (other.gameObject.GetComponent<NameTagComponent>().GetName() == "Enemy")
        {
            Open_CloseFunction();
        }
    }

    public void Open_CloseFunction()
    {
        if (doorState == 0)
        {
            //doorAnimator.SetBool("Open", true);
            doorState = 1;
        }
        else
        {
            //doorAnimator.SetBool("Open", false);
            doorState = 0;
        }
    }

    public void PlayVO()
    {
        bool changedAudio = false;

        // NOTE: Audio
        //if (!voSource.isPlaying())
        //{
        //    if (!changedAudio && forcelockedAudioCount < 2)
        //    {
        //        //select audio clip
        //        voSource.clip = forceLocked_VOLines[forcelockedAudioCount += 1];
        //        voSource.Play();

        //        //select subtitle
        //        mySubtitles.enabled = true;
        //        mySubtitles.text = myVOTexts[forcelockedAudioCount];
        //        changedAudio = true;
        //    }
        //    else
        //    {
        //        mySubtitles.enabled = false;
        //    }
        //}
        //else if (voSource.isPlaying())
        //{
        //    changedAudio = false;
        //}
    }
}
