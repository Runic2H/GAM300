﻿/*!*************************************************************************
****
\file Hiding.cs
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: csd3450
\date 12-12-2023
\brief  Gameplay script for player hiding from the monster
****************************************************************************
***/
using System;
using System.Reflection.Emit;
using ScriptAPI;

public class GalleryHiding : Script
{
    public bool interactable;
    public bool hiding;
    public Vector3 hidingPos;
    public Vector3 nonHidingPos;
    public float _RotationAngle;
    public GameObject player;
    public GameObject enemyPathfinding;
    public GameObject _flashlight;
    public GameObject _InteractUI;
    //public CheckGameState myGameState;
    public GameObject closet;
    [Header("AudioStuff")]
    //public AudioSource playerVOSource;
    public AudioComponent audioPlayer;
    String[] voClips;
    public String[] subtitles;
    int counter;
    public static bool playOnce = true;
    GameObject textmachine;

    private float timer = 1.0f;

    public float turnSpeed = 0.01f;

    public int numOfPaintingsTook = 0;

    public override void Awake()
    {
        numOfPaintingsTook = 0;

        //counter = 0;
        audioPlayer = gameObject.GetComponent<AudioComponent>();
        voClips = new string[3];
        voClips[0] = "pc_hideinclosetfirst";
        voClips[1] = "pc_wanderingcloset";
        voClips[2] = "pc_monstergoesaway2"; //i have to watch my back
        subtitles = new String[2];
        subtitles[0] = "Nothing inside";
        subtitles[1] = "But I could hide in here in case someone shows up";
    }

    public override void Start()
    {
        //_flashlight = player.GetComponent<Flashlight_Script>();
        hidingPos = closet.transform.GetPosition();
        _RotationAngle = 180.0f;

        timer = 0.8f;

    }

    public override void Update()
    {

        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            _InteractUI.SetActive(true);

            if (Input.GetKeyDown(Keycode.E) && hiding == false)
            {
                Hide();
                GhostMove();
               
            }
        }
        else if (hiding)
        {
            _InteractUI.SetActive(false);

            if (Input.GetKeyDown(Keycode.E))
            {
                //Console.WriteLine("There");
                hiding = false;
                interactable = true;

                Vector3 rotation = player.transform.GetRotation();
                Quaternion quat = new Quaternion(rotation);
                player.GetComponent<RigidBodyComponent>().SetPositionRotationAndVelocity(nonHidingPos, new Vector4(quat.X, quat.Y, quat.Z, quat.W), new Vector3(1, 1, 1).Normalize(), new Vector3(1, 1, 1).Normalize());

                // add if monster is finished
                player.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                player.GetComponent<FPS_Controller_Script>().enableHeadBob = true;
                _flashlight.SetActive(true);
                if (enemyPathfinding.GetComponent<GhostMovement>().galleryHideEventDone)
                {
                    audioPlayer.play(voClips[2]);
                    GameplaySubtitles.counter = 15;
                }
            }
        }
        else
        {
            _InteractUI.SetActive(false);
        }
    }

    public void Hide()
    {
        hiding = true;
        interactable = false;
        nonHidingPos = player.transform.GetPosition();

        Vector3 rotation = new Vector3(0, 0, 0);
        Quaternion quat = new Quaternion(rotation);
        Vector3 newPosition = new Vector3(closet.transform.GetPosition().X, player.transform.GetPosition().Y, closet.transform.GetPosition().Z);
        player.GetComponent<RigidBodyComponent>().SetPositionRotationAndVelocity(newPosition, new Vector4(quat.X, quat.Y, quat.Z, quat.W), new Vector3(0, 0, 0), new Vector3(0, 0, 0));
        player.transform.SetRotation(new Vector3(0, -_RotationAngle, 0));

        player.GetComponent<FPS_Controller_Script>().playerCanMove = false;
        player.GetComponent<FPS_Controller_Script>().enableHeadBob = false;
        if (player.GetComponent<Flashlight_Script>().flashAudio.finished(player.GetComponent<Flashlight_Script>().flashAudiostr[0]) && player.GetComponent<Flashlight_Script>().activateLight)
        {
            player.GetComponent<Flashlight_Script>().flashAudio.play(player.GetComponent<Flashlight_Script>().flashAudiostr[1]);
        }
        player.GetComponent<Flashlight_Script>().activateLight = false;
        _flashlight.SetActive(false);
    }

    public void GhostMove()
    {
        if (!p02.isPaintingCollected)
        {
            if (enemyPathfinding.GetComponent<GhostMovement>().hideEventDone == false)
            {
                if (enemyPathfinding.GetComponent<GhostMovement>().galleryHideEvent == false)
                {
                    enemyPathfinding.transform.SetPosition(new Vector3(-1920.0f, enemyPathfinding.transform.GetPosition().Y, 175.0f));
                    enemyPathfinding.GetComponent<GhostMovement>().galleryHideEvent = true;
                }
                enemyPathfinding.GetComponent<GhostMovement>().isChasingPlayer = false;
                enemyPathfinding.GetComponent<GhostMovement>().playSound = false;
            }
        }
        
        else
        {
            if (enemyPathfinding.GetComponent<GhostMovement>().hideEventDone == false)
            {
                if (enemyPathfinding.GetComponent<GhostMovement>().galleryChasingEvent == false)
                {
                    enemyPathfinding.transform.SetPosition(new Vector3(-1920.0f, enemyPathfinding.transform.GetPosition().Y, 175.0f));
                    enemyPathfinding.GetComponent<GhostMovement>().galleryChasingEvent = true;
                }
                enemyPathfinding.GetComponent<GhostMovement>().isChasingPlayer = false;
                enemyPathfinding.GetComponent<GhostMovement>().playSound = false;
            }
        }
    }
}
