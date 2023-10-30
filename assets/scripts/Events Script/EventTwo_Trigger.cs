using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EventTwo_Trigger : MonoBehaviour
{
    public CheckGameState myGameState;
    public Door_Script _BedroomDoubleDoor;
    public AudioSource lightAS;
    public AudioSource playerVOSource;
    public AudioClip voClip;
    public Text subtitles;

    [Header("Lighting Variables")]
    public Light[] _BedroomCellingLights;
    public Material NoEmission;
    public Material blueishEmission;
    public MeshRenderer cl;
    public MeshRenderer bulb;

    bool playedAudio;
    bool collided;

    private void Update()
    {
        if (collided)
        {
            if (!playedAudio)
            {
                playerVOSource.clip = voClip;
                playerVOSource.Play();
                subtitles.enabled = true;
                subtitles.text = "Martin (Internal): \"Empty... but I could’ve sworn someone opened that door.\"";
                playedAudio = true;
            }

            if (!playerVOSource.isPlaying && playedAudio)
            {
                subtitles.enabled = false;
                _BedroomDoubleDoor._DoorAudioSource.clip = _BedroomDoubleDoor._DoorSounds[1];
                _BedroomDoubleDoor.doorAnimator.SetBool("SlowOpen", false);
                _BedroomDoubleDoor.doorState = 0;
                _BedroomDoubleDoor.locked = true;
                _BedroomDoubleDoor._DoorAudioSource.enabled = true;

                StartCoroutine(StartDelay());
            }
        }
    }

    IEnumerator StartDelay()
    {
        yield return new WaitForSeconds(0.1f);

        lightAS.enabled = true;

        for (int i = 0; i < _BedroomCellingLights.Length; i++)
        {
            _BedroomCellingLights[i].enabled = false;
        }

        bulb.material = NoEmission;
        cl.material = NoEmission;

        StartCoroutine(deactivate());
    }

    IEnumerator deactivate()
    {
        yield return new WaitForSeconds(1f);
        _BedroomDoubleDoor.GetComponent<BoxCollider>().enabled = true;
        lightAS.enabled = false;
        gameObject.SetActive(false);
        myGameState._CurrentState = GameState.Gameplay;
    }

    private void OnTriggerEnter(Collider other)
    {
        _BedroomDoubleDoor._DoorAudioSource.enabled = false;

        if (other.gameObject.tag == "MainCamera")
        {
            collided = true;
            myGameState._CurrentState = GameState.Event2;
        }
    }
}
