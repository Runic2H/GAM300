using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EventOne_Script : MonoBehaviour
{
    [Header("Light Related Stuff")]
    public Animator _RightHallLights;
    public GameObject _BedroomLights;

    [Header("Door Related Stuff")]
    public Door_Script _BedroomDoubleDoor;
    public Door_Script _RightHallDoubleDoor;
    bool collided;

    public CheckGameState myGameState;
    public Image subtitleBG;
    public Text mySubtitle;
    public Text _FlashlightInstructions;
    public string[] voTexts;
    public AudioSource voSource;
    public AudioClip[] voLines;
    int currentVO = -1;

    // Update is called once per frame
    void Update()
    {
        if (collided)
        {
            _RightHallLights.SetBool("Play", true);
            _BedroomLights.SetActive(true);
            _RightHallDoubleDoor._DoorAudioSource.clip = _RightHallDoubleDoor._DoorSounds[0];

            StartCoroutine(StartFirstDelay());
        }
    }

    IEnumerator StartFirstDelay()
    {
        yield return new WaitForSeconds(0.3f);
        _RightHallDoubleDoor.locked = true;
        _RightHallDoubleDoor.doorAnimator.SetBool("Open", false);
        _RightHallDoubleDoor.doorState = 0;

        _RightHallDoubleDoor._DoorAudioSource.clip = _RightHallDoubleDoor._DoorSounds[0];
        _RightHallDoubleDoor._DoorAudioSource.enabled = true;

        StartCoroutine(StartSecondDelay());
    }

    IEnumerator StartSecondDelay()
    {
        yield return new WaitForSeconds(1f);
        _BedroomDoubleDoor._DoorAudioSource.clip = _BedroomDoubleDoor._DoorSounds[0];
        StartCoroutine(StartTutorial());
    }

    IEnumerator StartTutorial()
    {
        yield return new WaitForSeconds(1.5f);
        //FlashLightTutorial();
        mySubtitle.enabled = true;
        subtitleBG.enabled = true;
        _FlashlightInstructions.enabled = true;
        _FlashlightInstructions.text = "Press [F] to activate your flashlight";
        VO_Subtitles();
    }

    IEnumerator PlayDoorCreak()
    {
        yield return new WaitForSeconds(1f);
        _BedroomDoubleDoor._DoorAudioSource.enabled = true;

        FPS_Controller_Script _Player = GameObject.Find("Player").GetComponent<FPS_Controller_Script>();
        _Player.playerCanMove = true;
        _Player.cameraCanMove = true;
        StartCoroutine(Deactivate());
    }

    IEnumerator Deactivate()
    {
        yield return new WaitForSeconds(0.5f);
        this.gameObject.SetActive(false);
        _FlashlightInstructions.enabled = false;
        myGameState._CurrentState = GameState.Gameplay;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "MainCamera")
        {
            collided = true;
            myGameState._CurrentState = GameState.Event1;
        }
    }

    void VO_Subtitles()
    {
        bool changedAudio = false;

        if (!voSource.isPlaying)
        {
            if (!changedAudio && currentVO < 0)
            {
                //select audio clip
                voSource.clip = voLines[currentVO += 1];
                voSource.Play();

                //select subtitle
                mySubtitle.text = voTexts[currentVO];
                changedAudio = true;
            }
            else
            {
                StartCoroutine(PlayDoorCreak());
                mySubtitle.enabled = false;
                subtitleBG.enabled = false;

                _BedroomDoubleDoor.doorAnimator.SetBool("SlowOpen", true);
                _BedroomDoubleDoor.doorState = 1;
                _BedroomDoubleDoor.GetComponent<BoxCollider>().enabled = false;
                StartCoroutine(PlayDoorCreak());
            }
        }
        else if (voSource.isPlaying)
        {
            changedAudio = false;
        }
    }
}
