using System;
using System.ComponentModel.DataAnnotations;
using ScriptAPI;

public class LockPick1 : Script
{
    [Header("Tutorial UI Variables")]
/*  public Image _TutorialImage;
    public Sprite[] _TutorialImgSprites;
    public Text _Press2Continue;*/
    [SerializeField] int _TutorialStep;

/*  public Text mySubtitles;
    public Image mySubtitlesBG;
    public AudioSource myVOSource;*/
    public bool _TutorialCompleted;

    [Header("Lockpick Variables")]
    //public GameDataManager myGameDataManager;
    //public GameObject Door_UI;
    //public CameraComponent cam;
    //public CameraComponent playerCam;
    public TransformComponent innerLock;
    //public TransformComponent pickPosition;
    //public FPS_Controller_Script playerController;
    public GameObject player;
    public GameObject lockObject;
    public GameObject door;
    public string difficultyLvl;
    public float maxAngle = 90;
    public float lockSpeed = 10;
    public bool unlocked;
    public string[] lockSoundEffects;
    public string[] rattleSoundEffects;
    public string successVOclip;
    float delay = 0.4f;
    //public GameObject _NumOfTries;
    //public Text _AmtOfTries;

    [Range(1, 25)]
    public float lockRange = 10;

    [SerializeField] private int numOfTries;
    private float percentage;
    public float eulerAngle;
    public float eulerAngleDegree;
    private float unlockAngle;
    public Vector3 unlockRange;
    private float keyPressTime;
    public bool movePick;
    private bool deduct;
    private bool displayTutorial;
    [SerializeField] bool played;

    private Vector3 originalPosition;
    private int currentRattlePlaying = 0;
    public float timer = 1.2f;
    public bool passed = false;
    private bool failed = false;

    // Start is called before the first frame update
    override public void Awake() 
    {
        //lockSoundEffects = new string[3];
        //lockSoundEffects[0] = "Lock Turning Audio";
        //lockSoundEffects[1] = "lockpick success";
        //lockSoundEffects[2] = "lockpick_failtryl";

        rattleSoundEffects = new string[6];
        rattleSoundEffects[0] = "temp_lockrattle1";
        rattleSoundEffects[1] = "temp_lockrattle2";
        rattleSoundEffects[2] = "temp_lockrattle3";
        rattleSoundEffects[3] = "temp_lockrattle4";
        rattleSoundEffects[4] = "temp_lockrattle5";
        rattleSoundEffects[5] = "temp_lockrattle6";

        currentRattlePlaying = 0;

        successVOclip = "pc_lockpicksuccess1";

        newLock();
        passed = false;
    }

    // Update is called once per frame
    override public void Update()
    {
        lockSoundEffects = new string[3];
        lockSoundEffects[0] = "Lock Turning Audio";
        lockSoundEffects[1] = "lockpick success";
        lockSoundEffects[2] = "lockpick_failtryl";

        numOfTries = 5;
        eulerAngleDegree = toDegree(eulerAngle);
        AudioComponent audio = gameObject.GetComponent<AudioComponent>();

        if (!_TutorialCompleted)
        {
            //if (!myVOSource.isPlaying && !played)
            //{
            //    myVOSource.Play();
            //    mySubtitlesBG.enabled = true;
            //    mySubtitles.text = "Martin (Internal): Hopefully, I won’t forget how to do this.";
            //    played = true;

            //}
            //else if (!myVOSource.isPlaying && played)
            //{
            //    mySubtitles.text = "";
            //    mySubtitlesBG.enabled = false;
            //    _NumOfTries.SetActive(true);
            //    movePick = true;
            //    _TutorialCompleted = true;
            //}
        }
        else if (_TutorialCompleted)
        {
            //_NumOfTries.SetActive(_NumOfTries.GetEntityID(),true);

            #region Move Pick
            if (movePick)
            {
                Vector3 dir = Input.GetMousePosition() - new Vector3(Screen.width / 2, Screen.height / 2, 0);
                //Vector3 dir = Input.mousePosition - cam.WorldToScreenPoint(transform.position);

                eulerAngle = Vector3.Angle(dir, new Vector3(0, -1, 0));

                Vector3 cross = Vector3.Cross(new Vector3(0, 1, 0), dir);
                if (cross.Z < 0) { eulerAngle = -eulerAngle; }
                eulerAngle = Mathf.Clamp(eulerAngle, toRadians(-maxAngle), toRadians(maxAngle));

                transform.SetRotation(new Vector3(0, 0, eulerAngle));
                Vector2 addedPosition = new Vector2(-Mathf.Sin(eulerAngle) * 2.5f, Mathf.Cos(eulerAngle) * 2.5f);
                transform.SetPosition(new Vector3(originalPosition.X + addedPosition.X, originalPosition.X + addedPosition.Y, -15));
            }

            if (Input.GetKeyDown(Keycode.E))
            {
                movePick = false;
                keyPressTime = 1;
                audio.play(lockSoundEffects[0]);
            }
            if (Input.GetKeyUp(Keycode.E))
            {
                movePick = true;
                keyPressTime = 0;
                deduct = true;
                audio.stop(lockSoundEffects[0]);
            }
            #endregion

            #region Check if pick is at correct position

            float eulerAngleDeg = toDegree(eulerAngle);
            if (eulerAngleDeg > 180)
            {
                eulerAngleDeg = eulerAngleDeg - 360;
            }

            percentage = Mathf.Round(100 - Mathf.Abs(((eulerAngleDeg - unlockAngle) / 100) * 100));
            float maxRotation = (percentage / 100) * maxAngle;
            float lockRotation = maxRotation * keyPressTime;
            float lockLerp = Mathf.LerpAngle(toDegree(innerLock.GetRotation().Z), lockRotation, Time.deltaTime * lockSpeed);
            innerLock.SetRotation(new Vector3(0, 0, toRadians(lockLerp)));

            if (!movePick && (lockLerp >= maxRotation - 1))
            {
                Console.WriteLine("hmm");
                if (toDegree(eulerAngle) <= /*Mathf.Abs(*/unlockRange.Y && toDegree(eulerAngle) >= /*Mathf.Abs(*/unlockRange.X) // Means unlocked?
                {
                    movePick = true;
                    keyPressTime = 0;
                    Console.WriteLine("passed");
                    audio.stop(lockSoundEffects[0]);
                    audio.play(lockSoundEffects[1]);

                    passed = true;
                    //Coroutine(StartDelay());
                    //async Task<int> StartDelay()
                    //IEnumerator StartDelay()
                    //{
                    //    yield return new WaitForSeconds(1.2f);
                    //    playerController.enabled = true;
                    //    playerController.lockCursor = true;
                    //    playerCam.enabled = true;
                    //    Door_UI.SetActive(false);
                    //    unlocked = true;
                    //    _NumOfTries.SetActive(false);
                    //    lockObject.SetActive(false);
                    //}
                }
                else
                {
                    Vector3 rotation = transform.GetRotation();
                    float randomValue = ScriptAPI.Random.Range(-3.1415926535897931f * 100, 3.1415926535897931f * 100) / 20000;
                    transform.SetRotationZ(rotation.Z + randomValue);

                    if (Input.GetKeyDown(Keycode.E) || Input.GetKey(Keycode.E))
                    {
                        //if (!gameObject.GetComponent<AudioComponent>().isPlaying())
                        //{
                        //    delay -= Time.deltaTime;

                        //    if (delay <= 0)
                        //    {
                        //        gameObject.GetComponent<AudioComponent>().stop(rattleSoundEffects[currentRattlePlaying]);
                        //        currentRattlePlaying = (int)ScriptAPI.Random.Range(0, 6);
                        //        gameObject.GetComponent<AudioComponent>().play(rattleSoundEffects[currentRattlePlaying]);
                        //        delay = 0.2f;
                        //    }
                        //}
                    }

                    if (deduct == true)
                    {
                        numOfTries -= 1;
                        movePick = true;
                        deduct = false;
                    }

                    if (numOfTries <= 0)
                    {
                        //audio.play(lockSoundEffects[2]);
                        //gameObject.GetComponent<AudioComponent>().setVolume(0.5f);
                        movePick = false;

                        //Coroutine(Deactivate(), 1);

                        //IEnumerator<int> Deactivate()
                        //{
                        //    _NumOfTries.SetActive(false);
                        //    playerController.enabled = true;
                        //    playerController.lockCursor = true;
                        //    playerCam.enabled = true;
                        //    Door_UI.SetActive(false);
                        //    lockObject.SetActive(false);
                        //}
                    }
                }
            }
            #endregion

            //_AmtOfTries.text = numOfTries.ToString();

            if (numOfTries <= 1)
            {
                //_AmtOfTries.color = Color.red;
            }

            if (passed)
            {
                if (timer <= 0)
                {
                    //playerController.enabled = true;
                    //playerController.lockCursor = true;
                    //playerCam.enabled = true;
                    //Door_UI.SetActive(false);
                    //unlocked = true;
                    //_NumOfTries.SetActive(false);

                    lockObject.SetActive(lockObject.GetEntityID(), false);
                    player.SetActive(player.GetEntityID(), true);
                    GraphicsManagerWrapper.ToggleViewFrom2D(false);

                    door.SetActive(door.GetEntityID(), false);
                    //is_Enabled = false;

                    //audio.play(successVOclip);
                }
                else
                {
                    timer -= Time.deltaTime;
                }
            }

            if (failed)
            {
                if (timer <= 0)
                {
                    //_NumOfTries.SetActive(false);
                    //playerController.enabled = true;
                    //playerController.lockCursor = true;
                    //playerCam.enabled = true;
                    //Door_UI.SetActive(false);

                    //lockObject.SetActive(lockObject.GetEntityID(), false);
                    //GraphicsManagerWrapper.ToggleViewFrom2D(false);
                }
                else
                {
                    timer -= Time.deltaTime;
                }
            }
        }
    }

    public void newLock()
    {
        innerLock = GameObjectScriptFind("InnerLock").GetTransformComponent();
        //Cursor.visible = false;
        //gameObject.GetComponent<AudioComponent>().setVolume(1f);

        //Door_UI.SetActive(Door_UI.GetEntityID(), true);

        //_AmtOfTries.color = Color.white;
        keyPressTime = 0;
        unlocked = false;
        deduct = true;
        //playerController.is_Enabled = false;
        //playerCam. = false;
        //cam.transform.SetRotation(Quaternion(new))
        unlockAngle = ScriptAPI.Random.Range(-maxAngle + lockRange, maxAngle - lockRange);
        unlockRange = new Vector3(unlockAngle - lockRange, unlockAngle + lockRange, 0.0f);

        originalPosition = transform.GetPosition();

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
        movePick = true;
    }

    float toDegree(float radians)
    {
        return radians * (180 / 3.1415926535897931f);
    }
    float toRadians(float degree)
    {
        return degree * (3.1415926535897931f / 180);
    }
}
