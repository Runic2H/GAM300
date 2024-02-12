using System;
using System.ComponentModel.DataAnnotations;
using ScriptAPI;

public class LockPick1 : Script
{
    float toDegree(float radians)
    {
        return radians * (180 / 3.1415926535897931f);
    }
    float toRadians(float degree)
    {
        return degree * (3.1415926535897931f / 180);
    }

    // NEW

    //[Header("Tutorial UI Variables")]
    //public Image _TutorialImage;
    //public Sprite[] _TutorialImgSprites;
    //public Text _Press2Continue;
    //[SerializeField] int _TutorialStep;

    //public Text mySubtitles;
    //public Image mySubtitlesBG;

    public AudioSource myVOSource;
    public bool _TutorialCompleted;

    [Header("Lockpick Variables")]
    public GameDataManager myGameDataManager;
    public GameObject Door_UI;
    public CameraComponent cam;
    public CameraComponent playerCam;
    public TransformComponent innerLock;
    public TransformComponent pickPosition;
    public FPS_Controller_Script playerController;
    //public GameObject lockObject;
    public string difficultyLvl;
    public float maxAngle = 90;
    public float lockSpeed = 10;
    public bool unlocked;
    //public AudioClip[] lockSoundEffects;
    //public AudioClip[] rattleSoundEffects;
    public String[] lockSoundEffects;
    public String[] rattleSoundEffects;
    float delay = 0.4f;
    //public GameObject _NumOfTries;
    //public Text _AmtOfTries;

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

    private Vector3 originalPosition;
    private Vector3 originalRotation;
    AudioComponent audio;
    bool failed;
    bool passed;
    float timer;

    // Start is called before the first frame update
    override public void Awake()
    {
        lockSoundEffects = new String[3];
        lockSoundEffects[0] = "Lock Turning Audio";
        lockSoundEffects[1] = "lockpick success";
        lockSoundEffects[2] = "lockpick_failtryl";

        rattleSoundEffects = new String[6];
        rattleSoundEffects[0] = "temp_lockrattle1";
        rattleSoundEffects[1] = "temp_lockrattle2";
        rattleSoundEffects[2] = "temp_lockrattle3";
        rattleSoundEffects[3] = "temp_lockrattle4";
        rattleSoundEffects[4] = "temp_lockrattle5";
        rattleSoundEffects[5] = "temp_lockrattle6";

        audio = gameObject.GetComponent<AudioComponent>();

        newLock();
        originalPosition = transform.GetPosition();
        originalRotation = transform.GetRotation();
    }

    // Update is called once per frame
    override public void Update()
    {
        Input.Lock(false);

        if (!_TutorialCompleted)
        {
            // NOTE: Audio
            //if (!myVOSource.isPlaying() && !played)
            //{
            //    myVOSource.Play();
            //    mySubtitlesBG.enabled = true;
            //    mySubtitles.text = "Martin (Internal): Hopefully, I won’t forget how to do this.";
            //    played = true;

            //}
            //else if (!myVOSource.isPlaying() && played)
            //{
            //    mySubtitles.text = "";
            //    mySubtitlesBG.enabled = false;
            //    _NumOfTries.SetActive(true);
            //    movePick = true;
            //    _TutorialCompleted = true;
            //}
        }
        else
        {
            //_NumOfTries.SetActive(true);

            #region Move Pick
            if (movePick)
            {
                //Vector3 dir = Input.mousePosition - cam.WorldToScreenPoint(transform.position);
                Vector3 dir = Input.GetLocalMousePos() - new Vector3(Screen.width / 2, Screen.height / 2, 0);  //cam.WorldToScreenPoint(transform.GetPosition());

                //eulerAngle = Vector3.Angle(dir, Vector3.Up());
                eulerAngle = Vector3.Angle(dir, Vector3.Down());

                Vector3 cross = Vector3.Cross(Vector3.Up(), dir);
                if (cross.Z < 0) { eulerAngle = -eulerAngle; }
                eulerAngle = Mathf.Clamp(eulerAngle, toRadians(-maxAngle), toRadians(maxAngle));

                Quaternion rotateTo = Quaternion.AngleAxis(eulerAngle, Vector3.Forward());
                //transform.SetRotation(Quaternion.EulerAngle(rotateTo));

                Vector3 originalRotation = transform.GetRotation();
                transform.SetRotation(new Vector3(originalRotation.X, originalRotation.Y, eulerAngle));

                Vector2 newPosition = new Vector2(originalPosition.X * Mathf.Cos(eulerAngle) - originalPosition.Y * Mathf.Sin(eulerAngle),
                                                  originalPosition.X * Mathf.Sin(eulerAngle) + originalPosition.Y * Mathf.Cos(eulerAngle));
                transform.SetPosition(new Vector3(newPosition.X, newPosition.Y, originalPosition.Z));
            }

            if (Input.GetKeyDown(Keycode.E))
            {
                originalRotation = transform.GetRotation();
                movePick = false;
                keyPressTime = 1;
                // NOTE: Audio
                //GetComponent<AudioSource>().clip = lockSoundEffects[0];
                //GetComponent<AudioSource>().Play();
                audio.play(lockSoundEffects[0]);
            }
            if (Input.GetKeyUp(Keycode.E))
            {
                movePick = true;
                keyPressTime = 0;
                deduct = true;
            }
            #endregion

            #region Check if pick is at correct position
            float eulerAngleDegree = toDegree(eulerAngle);
            percentage = Mathf.Round(100 - Mathf.Abs(((eulerAngleDegree - unlockAngle) / 100) * 100));
            float maxRotation = (percentage / 100) * maxAngle;
            float lockRotation = maxRotation * keyPressTime;
            float lockLerp = Mathf.LerpAngle(toDegree(innerLock.GetRotation().Z), lockRotation, Time.deltaTime * lockSpeed);
            innerLock.SetRotation(new Vector3(0, 0, toRadians(lockLerp)));

            if (!movePick && (lockLerp >= maxRotation - 1))
            {
                if (eulerAngleDegree < unlockRange.Y && eulerAngleDegree > unlockRange.X)
                {
                    Console.WriteLine("hmm");
                    movePick = true;
                    keyPressTime = 0;
                    // NOTE: Audio
                    audio.play(lockSoundEffects[1]);
                    newLock();
                    timer = 1.2f;

                    //GetComponent<AudioSource>().clip = lockSoundEffects[1];
                    //GetComponent<AudioSource>().Play();

                    //StartCoroutine(StartDelay());
                    //IEnumerator StartDelay()
                    //{
                    //    yield return new WaitForSeconds(1.2f);
                    //    playerController.SetEnabled(true);
                    //    playerController.lockCursor = true;
                    //    playerCam.SetEnabled(true);
                    //    Door_UI.SetActive(false);
                    //    unlocked = true;
                    //    _NumOfTries.SetActive(false);
                    //    lockObject.SetActive(false);
                    //}
                }
                else
                {
                    //float randomRotation = ScriptAPI.Random.insideUnitCircle.x;
                    float randomRotation = ScriptAPI.Random.Range(-1,1); // NOTE: Not sure if insideUnitCircle keeps changing or is a fixed Vector2 that is reset on Start
                    transform.SetRotationZ(originalRotation.Z + (float)(randomRotation / 180.0 * Math.PI));

                    if (Input.GetKeyDown(Keycode.E) || Input.GetKey(Keycode.E))
                    {
                        // NOTE: Audio
                        if (audio.finished(lockSoundEffects[0]))
                        {
                            audio.stop(lockSoundEffects[0]);
                            delay -= Time.deltaTime;

                            if (delay <= 0)
                            {
                                // Not sure if there is a better way to do this
                                if (audio.finished(rattleSoundEffects[0]))
                                    audio.stop(rattleSoundEffects[0]);
                                if (audio.finished(rattleSoundEffects[1]))
                                    audio.stop(rattleSoundEffects[1]);
                                if (audio.finished(rattleSoundEffects[2]))
                                    audio.stop(rattleSoundEffects[2]);
                                if (audio.finished(rattleSoundEffects[3]))
                                    audio.stop(rattleSoundEffects[3]);
                                if (audio.finished(rattleSoundEffects[4]))
                                    audio.stop(rattleSoundEffects[4]);
                                if (audio.finished(rattleSoundEffects[5]))
                                    audio.stop(rattleSoundEffects[5]);

                                audio.play(rattleSoundEffects[(int)ScriptAPI.Random.Range(0, 5)]);
                                delay = 0.4f;
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
                        // NOTE: Audio
                        audio.play(lockSoundEffects[2]);
                        movePick = false;
                        timer = 1.0f;

                        //StartCoroutine(Deactivate());

                        //IEnumerator Deactivate()
                        //{
                        //    yield return new WaitForSeconds(1f);

                        //    _NumOfTries.SetActive(false);
                        //    playerController.SetEnabled(true);
                        //    playerController.lockCursor = true;
                        //    playerCam.SetEnabled(true);
                        //    Door_UI.SetActive(false);
                        //    lockObject.SetActive(false);
                        //}
                    }
                }
            }
            #endregion

            //_AmtOfTries.text = numOfTries.ToString();

            //if (numOfTries <= 1)
            //{
            //    _AmtOfTries.color = Color.red;
            //}

            if (passed)
            {
                if (timer <= 0)
                {
                    //    playerController.SetEnabled(true);
                    //    playerController.lockCursor = true;
                    //    playerCam.SetEnabled(true);
                    //    Door_UI.SetActive(false);
                    unlocked = true;
                    //    _NumOfTries.SetActive(false);
                    //    lockObject.SetActive(false);
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
                    //    _NumOfTries.SetActive(false);
                    //    playerController.SetEnabled(true);
                    //    playerController.lockCursor = true;
                    //    playerCam.SetEnabled(true);
                    //    Door_UI.SetActive(false);
                    //    lockObject.SetActive(false);
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
        audio.stop(lockSoundEffects[1]);
        audio.stop(lockSoundEffects[2]);
        Input.Lock(false);

        failed = false;
        passed = false;

        //Door_UI.SetActive(true);
        //_AmtOfTries.color = Color.white;
        keyPressTime = 0;
        unlocked = false;
        deduct = true;
        //playerController.SetEnabled(false);
        //playerCam.SetEnabled(false);
        cam.transform.SetRotation(new Vector3(0, 0, 0));
        unlockAngle = ScriptAPI.Random.Range(-maxAngle + lockRange, maxAngle - lockRange);
        unlockRange = new Vector2(unlockAngle - lockRange, unlockAngle + lockRange);

        numOfTries = 3;
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
