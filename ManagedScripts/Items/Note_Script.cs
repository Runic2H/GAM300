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

public class Note_Script : Script
{
    //RigidBodyComponent rigidBodyComponent; //for raycast?
    AudioComponent clip;
    AudioSource player;
    //bool once;
    String[] voClip;

    [SerializeField]
    public string Note_Name;
    public string Note_Texture;
    public string Note_VO;
    public GameObject? _InteractUI;

    public override void Awake()
    {
        Note_VO = "pc_checkreceipt";
        //once = true;
    }

    public override void Start()
    {
        //rigidBodyComponent = gameObject.GetComponent<RigidBodyComponent>();
        clip = gameObject.GetComponent<AudioComponent>();
        player = gameObject.GetComponent<AudioSource>();
    }

    public override void Update()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            Console.WriteLine("Note");
            if (Input.GetKeyDown(Keycode.E))
            {
                Console.WriteLine("Picked up note");
                InventoryScript.addNoteIntoInventory(Note_Name, Note_Texture);
                gameObject.GetComponent<GraphicComponent>().SetView2D(true);
                gameObject.SetActive(false);
                clip.play(Note_VO);
            }
        }
        
    }

    public override void LateUpdate()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            _InteractUI.SetActive(true);
        }
        else
        {
            _InteractUI.SetActive(false);
        }
    }
}