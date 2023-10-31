using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EventThree_Script : MonoBehaviour
{
    public CheckGameState myGameState;
    public Door_Script _BedroomSingleDoor;
    public Hiding _Hiding;
    public GameObject _Enemy;
    public AudioSource _AmbienceAudio;

    [SerializeField] int eventState = 0;
    [SerializeField] float delay = 0.5f;

    [SerializeField] bool displayTutorial;
    public GameDataManager myGameDataManager;
    public GameObject _HidingUI;
    public Text _Press2Continue;
    public Image _TutorialImage;

    [Header("VO Stuff")]
    public AudioClip[] playerVO;
    public AudioSource playerAS;
    public Text mySubtitles;
    public Image subtitleBG;
    public string[] myTexts;
    int currentVO = -1;
    float HideTutorialDelay = 0;

    [Header ("Lighting Stuff")]
    public AudioSource cellingLights_AudioSource;
    public Light[] cellingLights;

    // Start is called before the first frame update
    void Start()
    {
        _BedroomSingleDoor._DoorAudioSource.clip = _BedroomSingleDoor._DoorSounds[0];
        _BedroomSingleDoor._DoorAudioSource.Play();
        _BedroomSingleDoor._DoorAudioSource.loop = true;
        myGameState._CurrentState = GameState.Event3;
        displayTutorial = true;
        mySubtitles.enabled = true;
        subtitleBG.enabled = true;
    }

    // Update is called once per frame
    void Update()
    {
        if (displayTutorial)
        {
            bool changedAudio = false;

            if (!playerAS.isPlaying)
            {
                if (!changedAudio && currentVO < 0)
                {
                    //select audio clip
                    playerAS.clip = playerVO[currentVO += 1];
                    playerAS.Play();

                    //select subtitle
                    mySubtitles.text = myTexts[currentVO];
                    changedAudio = true;
                }
                else
                {
                    HideTutorialDelay = HideTutorialDelay += Time.deltaTime;
                    mySubtitles.text = "Press [E] near a closet to hide";

                    if (HideTutorialDelay >= 3f)
                    {
                        subtitleBG.enabled = false;
                        mySubtitles.enabled = false;
                        displayTutorial = false;
                    }
                }
            }
            else if (playerAS.isPlaying)
            {
                changedAudio = false;
            }
        }

        if (_Hiding.hiding && eventState == 0)
        {
            _BedroomSingleDoor._DoorAudioSource.Stop();
            cellingLights_AudioSource.enabled = true;
            eventState = 1;
            mySubtitles.enabled = false;
            subtitleBG.enabled = false;
        }

        if (eventState == 0)
        {
            _AmbienceAudio.enabled = true;

            if (_AmbienceAudio.volume <= 0.25f)
            {
                _AmbienceAudio.volume += 0.05f;
            }
        }
        else if (eventState == 1)
        {
            delay -= Time.deltaTime;

            if (delay <= 0)
            {
                for (int i = 0; i < cellingLights.Length; i++)
                {
                    cellingLights[i].enabled = true;
                }

                cellingLights_AudioSource.enabled = false;

                _Enemy.SetActive(true);
            }
        }
        else if (eventState == 2)
        {
            delay -= Time.deltaTime;

            if (delay <= 0)
            {
                _Enemy.GetComponent<Pathfinding>()._canMove = true;

                delay = 5f;
                eventState = 3;
            }
        }
        else if (eventState == 3)
        {
            if (delay > 0)
            {
                delay -= Time.deltaTime;
            }

            if (delay <= 0)
            {
                for (int i = 0; i < cellingLights.Length; i++)
                {
                    cellingLights[i].enabled = false;
                }

                cellingLights_AudioSource.enabled = true;

                _Enemy.GetComponent<MeshRenderer>().enabled = false;

                delay = 0.5f;
                eventState = 4;
            }
        }
        else if (eventState == 4)
        {
            if (delay > 0)
            {
                delay -= Time.deltaTime;
                cellingLights_AudioSource.enabled = false;
            }

            if (delay <= 0)
            {
                if (_AmbienceAudio.volume <= 0f)
                {
                    _AmbienceAudio.enabled = false;
                }
                else
                {
                    _AmbienceAudio.volume -= 0.05f;
                }

                _Enemy.SetActive(false);

                for (int i = 0; i < cellingLights.Length; i++)
                {
                    cellingLights[i].enabled = true;
                }

                cellingLights_AudioSource.enabled = true;

                _BedroomSingleDoor.forcedLocked = false;
                _BedroomSingleDoor.locked = false;

                bool changedAudio = false;

                if (!playerAS.isPlaying && cellingLights_AudioSource.enabled)
                {
                    if (!changedAudio && currentVO < 3)
                    {
                        //select audio clip
                        playerAS.clip = playerVO[currentVO += 1];
                        playerAS.Play();

                        //select subtitle
                        mySubtitles.text = myTexts[currentVO];
                        changedAudio = true;
                        mySubtitles.enabled = true;
                        subtitleBG.enabled = true;
                    }
                    else
                    {
                        subtitleBG.enabled = false;
                        mySubtitles.enabled = false;
                        myGameState._CurrentState = GameState.Gameplay;
                        playerAS.clip = null;
                        cellingLights_AudioSource.enabled = false;
                        this.gameObject.SetActive(false);
                    }
                }
                else if (playerAS.isPlaying)
                {
                    changedAudio = false;
                }
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.name == "Enemy" && delay <= 0)
        {
            _Enemy.GetComponent<Pathfinding>()._canMove = false;
            delay = 3;
            eventState = 2;
        }
    }
}
