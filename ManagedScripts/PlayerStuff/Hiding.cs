﻿using System;
using System.Reflection.Emit;
using ScriptAPI;

public class Hiding : Script
{
    public bool interactable;
    public bool hiding;
    public Vector3 hidingPos;
    public Vector3 nonHidingPos;
    public float _RotationAngle;
    public GameObject player;
    public GhostMovement? enemyPathfinding;
    public GameObject _flashlight;
    public GameObject? _InteractUI;
    public CheckGameState myGameState;
    public GameObject closet;
    public Quaternion rotGoal;
    /*[Header("AudioStuff")]
    public AudioSource playerVOSource;
    public AudioClip voClip;
    public Text subtitles;*/

    private float timer = 1.0f;

    public float turnSpeed = 0.01f;

public override void Awake()
    {
    }

    public override void Start()
    {
        //_flashlight = player.GetComponent<Flashlight_Script>();
        hidingPos = closet.transform.GetPosition();
        _RotationAngle = 180;
    }

    public override void Update()
    {
        
        if (interactable && gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            _InteractUI.SetActive(true);
            if (Input.GetKeyDown(Keycode.E) && hiding == false)
            {
                Console.WriteLine("Here");
                hiding = true;
                interactable = false;
                nonHidingPos = player.transform.GetPosition();
                player.transform.SetPosition(closet.transform.GetPosition());

                Vector3 vec3 = new Vector3(0, _RotationAngle, 0);
                player.transform.SetRotation(vec3);

                player.GetComponent<FPS_Controller_Script>().playerCanMove = false;
                player.GetComponent<FPS_Controller_Script>().enableHeadBob = false;
                if (player.GetComponent<Flashlight_Script>().flashAudio.finished(player.GetComponent<Flashlight_Script>().flashAudiostr) && player.GetComponent<Flashlight_Script>().activateLight)
                {
                    player.GetComponent<Flashlight_Script>().flashAudio.play(player.GetComponent<Flashlight_Script>().flashAudiostr);
                }
                player.GetComponent<Flashlight_Script>().activateLight = false;
                _flashlight.SetActive(false);
            }
        }
        else if (hiding)
        {
            _InteractUI.SetActive(false);
            if (Input.GetKeyDown(Keycode.E))
            {
                Console.WriteLine("There");
                hiding = false;
                interactable = true;
                player.transform.SetPosition(nonHidingPos);
                player.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                player.GetComponent<FPS_Controller_Script>().enableHeadBob = true;
                _flashlight.SetActive(true);
                //Input.KeyRelease(Keycode.E);
            }
        }
        else
        {
            _InteractUI.SetActive(false);
        }
        
    }

    /*private void OnTriggerEnter(GameObject other)
    {
        if (other.GetComponent<NameTagComponent>().GetName() == "Enemy" && hiding == true)
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
    }*/
}
