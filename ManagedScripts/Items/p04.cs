/*!*************************************************************************
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

public class p04 : Script
{
    [SerializeField]
    public string Painting_Name;
    public string Painting_Texture;

    [Header("AudioStuff")]
    public AudioComponent AudioPlayer;

    public GameObject hidingGameObject;
    public GameObject ghost;
    public static bool isPaintingCollected;
    public static bool isInteractable;

    override public void Awake()
    {
        AudioPlayer = gameObject.GetComponent<AudioComponent>();
        isPaintingCollected = false;
        isInteractable = false;
    }

    public override void Start()
    {
    }

    // Update is called once per frame
    override public void Update()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit() && gameObject.GetComponent<RigidBodyComponent>().IsPlayerCast())
        {
            Console.WriteLine("p04");
            isInteractable = true;

            if (Input.GetKeyDown(Keycode.E))
            {
                Console.WriteLine("Picked up p04");
                isPaintingCollected = true;
                InventoryScript.addPaintingIntoInventory(Painting_Name, Painting_Texture);

                // View Object Stuff
                gameObject.GetComponent<GraphicComponent>().SetView2D(true);
                gameObject.transform.SetPosition(new Vector3(-10000.0f, -10000.0f, -10000.0f));
                gameObject.transform.SetRotation(new Vector3(-0.0f, -0.0f, -0.0f));
                gameObject.SetActive(false);

                // Trigger Painting Event
                AudioPlayer.play("gallery_movepainting");

                // hiding event 
                //hidingGameObject.GetComponent<Hiding>().numOfPaintingsTook++;
                //if (hidingGameObject.GetComponent<Hiding>().numOfPaintingsTook == 1)
                //{
                //    ghost.GetComponent<GhostMovement>().PlayMonsterWalkingSoundInitial();
                //}
            }
        }
        else
        {
            isInteractable = false;
        }
    }
}
