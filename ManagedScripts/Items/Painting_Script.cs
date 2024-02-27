﻿/*!*************************************************************************
****
\file Painting_Script.cs
\author Celine Leong
\par DP email: jiayiceline.leong@digipen.edu
\par Course: csd3450
\date 15-1-2024
\brief  Gameplay script for player interaction with paintings
****************************************************************************
***/
using Microsoft.VisualBasic;
using ScriptAPI;
using System;

public class Painting_Script : Script
{
    private GameObject playerObject;
    //RigidBodyComponent rigidBodyComponent; //for raycast?

    [SerializeField]
    public string Painting_Name;
    public string Painting_Texture;
    public bool opened;
    public GameObject? _InteractUI;

    //public Animator _PaintingAnimator;
    //public Flashlight_Script _FlashlightScript;
    //private GraphicComponent _color;

    [Header("AudioStuff")]
    public AudioComponent AudioPlayer;
    public String[] voClip;

    public float timer;
    public GameObject hidingGameObject;
    public GameObject ghost;

    override public void Awake()
    {
        voClip = new string[3];
        voClip[0] = "pc_stealpainting1";
        voClip[1] = "pc_shinelightbeforereceipt";
        voClip[2] = "pc_shinelightafterreceipt";
        AudioPlayer = gameObject.GetComponent<AudioComponent>();
        //_color.a = 1;
        //timer = 1.0f;
        //Console.WriteLine("Painting script");
    }

    public override void Start()
    {
        playerObject = GameObjectScriptFind("player");
        //rigidBodyComponent = gameObject.GetComponent<RigidBodyComponent>();
    }

    // Update is called once per frame
    override public void Update()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            Console.WriteLine("Painting");
            AudioPlayer.play(voClip[1]);

            if (Input.GetKeyDown(Keycode.E))
            {
                Console.WriteLine("Picked up painting");
                InventoryScript.addPaintingIntoInventory(Painting_Name, Painting_Texture);
                gameObject.GetComponent<GraphicComponent>().SetView2D(true);
                gameObject.SetActive(false);
                AudioPlayer.play(voClip[0]);

                // hiding event 
                hidingGameObject.GetComponent<Hiding>().numOfPaintingsTook++;
                if (hidingGameObject.GetComponent<Hiding>().numOfPaintingsTook == 1)
                {
                    ghost.GetComponent<GhostMovement>().PlayMonsterWalkingSoundInitial();
                }
            }
        }
    }

    public override void LateUpdate()
    {
        //if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        //{
        //    _InteractUI.SetActive(true);
        //}
        //else
        //{
        //    _InteractUI.SetActive(false);
        //}
    }

    public bool isWithinRange()
    {
        Vector3 itemPos = gameObject.transform.GetPosition();
        Vector3 playerPos = playerObject.transform.GetPosition();
        float distance = Vector3.Distance(itemPos, playerPos);
        //Console.WriteLine(distance);
        return distance < 100.0;
    }
}
