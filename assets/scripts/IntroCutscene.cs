using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class IntroCutscene : MonoBehaviour
{
    public CheckGameState myGameState;
    public AudioClip[] _IntroVO;
    public Sprite[] _IntroSprite;
    public Image myIntroImage;
    public Text mySubtitles;
    public GameObject introCutSceneUI;
    public FPS_Controller_Script myPlayer;


    private AudioSource myAudioSource;
    private bool finishedJournalScene;
    [SerializeField] private int currentVO = -1;
    [SerializeField] private GameObject dialogueBox;
    public DialogueObject currentDialogue;

    // Start is called before the first frame update
    void Start()
    {
        myAudioSource = GetComponent<AudioSource>();
    }

    // Update is called once per frame
    void Update()
    {
        VO_Subtitles(currentDialogue);

        if (myGameState._CurrentState == GameState.Intro)
        {
            if (finishedJournalScene)
            {
                #region Play intro

                if (currentVO == 6)
                {
                    myIntroImage.sprite = _IntroSprite[1];
                }
                else if (currentVO == 8)
                {
                    myIntroImage.sprite = _IntroSprite[2];
                }
                else if (currentVO == 10)
                {
                    myIntroImage.sprite = _IntroSprite[3];
                }
                else if (currentVO == 12)
                {
                    myIntroImage.sprite = _IntroSprite[4];
                }
                else if (currentVO == 14)
                {
                    myIntroImage.sprite = _IntroSprite[5];
                }
                else if (currentVO == 15)
                {
                    myIntroImage.sprite = _IntroSprite[6];
                }
                else if (currentVO == 16)
                {
                    myIntroImage.sprite = _IntroSprite[7];
                }
                #endregion
            }
            else
            {
                StartDisappearing();
            }
        }
        else
        {
            introCutSceneUI.SetActive(false);
            gameObject.SetActive(false);
            myPlayer.enabled = true;
        }

        if (Input.GetKeyDown(KeyCode.Space))
        {
            myGameState._CurrentState = GameState.LockpickTutorial;
        }
    }

    void StartDisappearing()
    {
        Color _color = myIntroImage.color;
        _color.r -= 0.05f * Time.deltaTime;
        _color.g -= 0.05f * Time.deltaTime;
        _color.b -= 0.05f * Time.deltaTime;
        myIntroImage.color = _color;

        if (_color.r <= 0)
        {
            finishedJournalScene = true;
            _color.r = 1;
            _color.g = 1;
            _color.b = 1;
            myIntroImage.color = _color;
            myIntroImage.sprite = _IntroSprite[0];
        }
    }

    void VO_Subtitles(DialogueObject dialogueObject)
    {
        bool changedAudio = false;

        if (!myAudioSource.isPlaying)
        {
            if (!changedAudio && currentVO < 17)
            {
                //select audio clip
                myAudioSource.clip = _IntroVO[currentVO += 1];
                myAudioSource.Play();

                //select subtitle
                mySubtitles.text = dialogueObject.dialogueLines[currentVO].dialogue;
                changedAudio = true;
            }
            else
            {
                myGameState._CurrentState = GameState.LockpickTutorial;
            }
        }
        else if (myAudioSource.isPlaying)
        {
            changedAudio = false;
        }
    }
}
