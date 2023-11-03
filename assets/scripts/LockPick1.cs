using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class LockPick1 : MonoBehaviour
{
    [Header("Tutorial UI Variables")]
    public Image _TutorialImage;
    public Sprite[] _TutorialImgSprites;
    public Text _Press2Continue;
    [SerializeField] int _TutorialStep;

    public Text mySubtitles;
    public Image mySubtitlesBG;
    public AudioSource myVOSource;
    public bool _TutorialCompleted;

    [Header("Lockpick Variables")]
    public GameDataManager myGameDataManager;
    public GameObject Door_UI;
    public Camera cam;
    public Camera playerCam;
    public Transform innerLock;
    public Transform pickPosition;
    public FPS_Controller_Script playerController;
    public GameObject lockObject;
    public string difficultyLvl;
    public float maxAngle = 90;
    public float lockSpeed = 10;
    public bool unlocked;
    public AudioClip[] lockSoundEffects;
    public AudioClip[] rattleSoundEffects;
    float delay = 0.4f;
    public GameObject _NumOfTries;
    public Text _AmtOfTries;

    [Range(1, 25)]
    public float lockRange = 10;

    [SerializeField] private int numOfTries;
    private float percentage;
    private float eulerAngle;
    private float unlockAngle;
    private Vector2 unlockRange;
    private float keyPressTime;
    private bool movePick;
    private bool deduct;
    private bool displayTutorial;
    [SerializeField] bool played;

    // Start is called before the first frame update
    void Awake()
    {
        newLock();
    }

    // Update is called once per frame
    void Update()
    {
        if (!_TutorialCompleted)
        {
            if (!myVOSource.isPlaying && !played)
            {
                myVOSource.Play();
                mySubtitlesBG.enabled = true;
                mySubtitles.text = "Martin (Internal): Hopefully, I won’t forget how to do this.";
                played = true;

            }
            else if (!myVOSource.isPlaying && played)
            {
                mySubtitles.text = "";
                mySubtitlesBG.enabled = false;
                _NumOfTries.SetActive(true);
                movePick = true;
                _TutorialCompleted = true;
            }
        }
        else if (_TutorialCompleted)
        {
            _NumOfTries.SetActive(true);

            #region Move Pick
            if (movePick)
            {
                Vector3 dir = Input.mousePosition - cam.WorldToScreenPoint(transform.position);

                eulerAngle = Vector3.Angle(dir, Vector3.up);

                Vector3 cross = Vector3.Cross(Vector3.up, dir);
                if (cross.z < 0) { eulerAngle = -eulerAngle; }

                eulerAngle = Mathf.Clamp(eulerAngle, -maxAngle, maxAngle);

                Quaternion rotateTo = Quaternion.AngleAxis(eulerAngle, Vector3.forward);
                transform.rotation = rotateTo;
            }

            if (Input.GetKeyDown(KeyCode.E))
            {
                movePick = false;
                keyPressTime = 1;
                GetComponent<AudioSource>().clip = lockSoundEffects[0];
                GetComponent<AudioSource>().Play();
            }
            if (Input.GetKeyUp(KeyCode.E))
            {
                movePick = true;
                keyPressTime = 0;
                deduct = true;
            }
            #endregion

            #region Check if pick is at correct position
            percentage = Mathf.Round(100 - Mathf.Abs(((eulerAngle - unlockAngle) / 100) * 100));
            float lockRotation = ((percentage / 100) * maxAngle) * keyPressTime;
            float maxRotation = (percentage / 100) * maxAngle;
            float lockLerp = Mathf.LerpAngle(innerLock.eulerAngles.z, lockRotation, Time.deltaTime * lockSpeed);
            innerLock.eulerAngles = new Vector3(0, 0, lockLerp);

            if (lockLerp >= maxRotation - 1)
            {
                if (eulerAngle < unlockRange.y && eulerAngle > unlockRange.x)
                {
                    movePick = true;
                    keyPressTime = 0;
                    GetComponent<AudioSource>().clip = lockSoundEffects[1];
                    GetComponent<AudioSource>().Play();

                    StartCoroutine(StartDelay());
                    IEnumerator StartDelay()
                    {
                        yield return new WaitForSeconds(1.2f);
                        playerController.enabled = true;
                        playerController.lockCursor = true;
                        playerCam.enabled = true;
                        Door_UI.SetActive(false);
                        unlocked = true;
                        _NumOfTries.SetActive(false);
                        lockObject.SetActive(false);
                    }
                }
                else
                {
                    float randomRotation = Random.insideUnitCircle.x;
                    transform.eulerAngles += new Vector3(0, 0, Random.Range((-randomRotation - 1), (randomRotation + 1)));

                    if (Input.GetKeyDown(KeyCode.E) || Input.GetKey(KeyCode.E))
                    {
                        if (!GetComponents<AudioSource>()[1].isPlaying)
                        {
                            delay -= Time.deltaTime;

                            if (delay <= 0)
                            {
                                GetComponents<AudioSource>()[1].clip = rattleSoundEffects[Random.Range(0, rattleSoundEffects.Length)];
                                GetComponents<AudioSource>()[1].Play();
                                delay = 0.2f;
                            }
                        }
                    }

                    if (deduct == true)
                    {
                        numOfTries -= 1;
                        deduct = false;
                    }

                    if (numOfTries <= 0)
                    {
                        GetComponent<AudioSource>().clip = lockSoundEffects[2];
                        GetComponent<AudioSource>().volume = 0.5f;
                        GetComponent<AudioSource>().Play();
                        movePick = false;

                        StartCoroutine(Deactivate());

                        IEnumerator Deactivate()
                        {
                            yield return new WaitForSeconds(1f);

                            _NumOfTries.SetActive(false);
                            playerController.enabled = true;
                            playerController.lockCursor = true;
                            playerCam.enabled = true;
                            Door_UI.SetActive(false);
                            lockObject.SetActive(false);
                        }
                    }
                }
            }
            #endregion

            _AmtOfTries.text = numOfTries.ToString();

            if (numOfTries <= 1)
            {
                _AmtOfTries.color = Color.red;
            }
        }
    }

    public void newLock()
    {
        Cursor.visible = false;
        Cursor.lockState = CursorLockMode.None;
        GetComponent<AudioSource>().volume = 1f;
        Door_UI.SetActive(true);
        _AmtOfTries.color = Color.white;
        keyPressTime = 0;
        unlocked = false;
        deduct = true;
        playerController.enabled = false;
        playerCam.enabled = false;
        cam.transform.rotation = Quaternion.Euler(new Vector3(0, 0, 0));
        unlockAngle = Random.Range(-maxAngle + lockRange, maxAngle - lockRange);
        unlockRange = new Vector2(unlockAngle - lockRange, unlockAngle + lockRange);

        if (difficultyLvl == "Easy")
        {
            numOfTries = 10;
        }
        else if (difficultyLvl == "Normal")
        {
            numOfTries = 5;
        }
        else if (difficultyLvl == "Hard")
        {
            numOfTries = 3;
        }

        if (_TutorialCompleted)
        {
            movePick = true;
        }
    }
}