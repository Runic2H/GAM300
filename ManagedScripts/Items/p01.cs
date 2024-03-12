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

public class p01 : Script
{
    [SerializeField]
    public string Painting_Name;
    public string Painting_Texture;

    public GameObject _InteractUI;

    [Header("AudioStuff")]
    public AudioComponent AudioPlayer;

    public GameObject hidingGameObject;
    public GameObject ghost;
    public static bool isPaintingCollected;


    override public void Awake()
    {
        AudioPlayer = gameObject.GetComponent<AudioComponent>();
        isPaintingCollected = false;
    }

    public override void Start()
    {
        //rigidBodyComponent = gameObject.GetComponent<RigidBodyComponent>();
    }

    // Update is called once per frame
    override public void Update()
    {
        //if(GalleryLetter.isNotePicked) // Don't allow player to proceed with puzzle before getting the hint.
        {
            if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit() && gameObject.GetComponent<RigidBodyComponent>().IsPlayerCast())
            {
                Console.WriteLine("p01");
                _InteractUI.SetActive(true);

                if (Input.GetKeyDown(Keycode.E))
                {
                    Hiding.playOnce = false;
                    Console.WriteLine("Picked up p01");
                    isPaintingCollected = true;
                    InventoryScript.addPaintingIntoInventory(Painting_Name, Painting_Texture);

                    // View Object Stuff
                    gameObject.GetComponent<GraphicComponent>().SetView2D(true);
                    gameObject.transform.SetPosition(new Vector3(-10000.0f, -10000.0f, -10000.0f));
                    gameObject.transform.SetRotation(new Vector3(-0.0f, -0.0f, -0.0f));
                    gameObject.SetActive(false);

                    // Trigger Painting Event
                    AudioPlayer.play("gallery_movepainting");
                    AudioPlayer.play("mon_patrol4");
                    GameplaySubtitles.counter = 8;

                    // hiding event 
                    GalleryHiding.GhostShouldMove = true;
                    GalleryHiding.timeLimit = 10.0f;
                    GalleryHiding.GhostMoved = false;
                    ghost.GetComponent<GhostMovement>().PlayMonsterWalkingSoundInitial();
                }
            }
        }
        
    }

    public override void LateUpdate()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit() && gameObject.GetComponent<RigidBodyComponent>().IsPlayerCast())
        {
            _InteractUI.SetActive(true);
        }
        else
        {
            _InteractUI.SetActive(false);
        }
    }
}
