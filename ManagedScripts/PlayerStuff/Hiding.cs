using System;
using ScriptAPI;

public class Hiding : Script
{
    public bool interactable;
    public bool hiding;
    public Vector3 hidingPos;
    public Vector3 nonHidingPos;
    public float _RotationAngle;
    public GameObject player;
    public GhostMovement enemyPathfinding;
    public Flashlight_Script _flashlight;
    public GameObject _InteractUI;
    public CheckGameState myGameState;
    public GameObject closet;
    /*[Header("AudioStuff")]
    public AudioSource playerVOSource;
    public AudioClip voClip;
    public Text subtitles;*/

    bool playedAudio;


    public override void Awake()
    {
    }

    public override void Start()
    {
    }

    public override void Update()
    {
        player = GameObjectScriptFind("Player");
        nonHidingPos = new Vector3(2257,250,-111);
        closet = GameObjectScriptFind("Body2");
        _flashlight = player.GetComponent<Flashlight_Script>();
        hidingPos = closet.transform.GetPosition();
        _RotationAngle = 180;
        if (interactable && closet.GetSphereColliderComponent().GetIsInteract())
        {
            if (Input.GetKeyDown(Keycode.E) && hiding == false)
            {
                Console.WriteLine("Here");
                //_InteractUI.SetActive(_InteractUI.GetEntityID(), false);
                hiding = true;
                interactable = false;
                player.transform.SetPosition(hidingPos);
                Vector3 vec3 = new Vector3(0, _RotationAngle, 0);
                player.transform.SetRotation(vec3);
                player.GetComponent<FPS_Controller_Script>().playerCanMove = false;
                player.GetComponent<FPS_Controller_Script>().enableHeadBob = false;
                _flashlight.activateLight = false;
                _flashlight.is_Enabled = false;


                /*if (gameObject.GetNameTagComponent().GetName() == "Bedroom_Body" && myGameState._CurrentState == GameState.Gameplay)
                {
                    if (!playedAudio)
                    {
                        playerVOSource.clip = voClip;
                        playerVOSource.Play();
                        subtitles.enabled = true;
                        subtitles.text = "Martin (Internal): \"Nothing inside, but I could hide in here in case someone shows up.\"";
                        playedAudio = true;
                    }

                    if (!playerVOSource.isPlaying && playedAudio)
                    {
                        subtitles.enabled = false;
                    }
                }*/

                Input.KeyRelease(Keycode.E);
            }
        }
        else if (hiding)
        {
            if (Input.GetKeyDown(Keycode.E))
            {
                Console.WriteLine("There");
                hiding = false;
                interactable = false;
                player.transform.SetPosition(nonHidingPos);
                player.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                player.GetComponent<FPS_Controller_Script>().enableHeadBob = true;
                _flashlight.is_Enabled = true;
                Input.KeyRelease(Keycode.E);
            }
        }
        
    }

    private void OnTriggerEnter(GameObject other)
    {
        if (other.GetNameTagComponent().GetName() == "Enemy" && hiding == true)
        {
            if (enemyPathfinding.isChasingPlayer && hiding == true)
            {
                player.transform.SetPosition(nonHidingPos);
                hiding = false;
                interactable = false;
                _flashlight.is_Enabled = true;
                //Debug.LogError("Pulled Out");
                //Play Attack Player Animation
            }
        }
    }
}
