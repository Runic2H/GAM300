﻿/*!*************************************************************************
****
\file Note_Script.cs
\author Celine Leong
\par DP email: jiayiceline.leong@digipen.edu
\par Course: csd3450
\date 15-1-2024
\brief  Gameplay script for player interaction with notes
****************************************************************************
***/
using ScriptAPI;
using System;
using System.Threading.Tasks.Dataflow;

public class GalleryLetter : Script
{
    //RigidBodyComponent rigidBodyComponent; //for raycast?
    AudioComponent clip;
    AudioSource player;
    //bool once;
    String[] voClip;

    [SerializeField]
    public string Note_Name;
    public string Note_Texture;
    public static bool isNotePicked = false;
    public static bool isInteractable;
    public override void Awake()
    {
    }

    public override void Start()
    {
        //rigidBodyComponent = gameObject.GetComponent<RigidBodyComponent>();
        clip = gameObject.GetComponent<AudioComponent>();
        player = gameObject.GetComponent<AudioSource>();
        isInteractable = false;
    }

    public override void Update()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit() && gameObject.GetComponent<RigidBodyComponent>().IsPlayerCast())
        {
            Console.WriteLine("Gallery Letter");
            isInteractable = true;
            if (Input.GetKeyDown(Keycode.E))
            {
                Console.WriteLine("Picked up gallery letter");

                // Add to Inventory
                InventoryScript.addNoteIntoInventory(Note_Name, Note_Texture);

                // ViewObject Stuff
                //gameObject.GetComponent<GraphicComponent>().SetView2D(true);
                gameObject.transform.SetPosition(new Vector3(-10000.0f, -10000.0f, -10000.0f));
                gameObject.transform.SetRotation(new Vector3(-0.0f, -0.0f, -0.0f));
                gameObject.SetActive(false);

                // Trigger Note Event
                clip.play("pc_moreinthebasement");
                isNotePicked = true;
                GameplaySubtitles.counter = 41;
            }
        }
        else
        {
            isInteractable = false;
        }
    }
}