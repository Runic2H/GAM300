/*!*************************************************************************
****
\file Item_Script.cs
\author Celine Leong
\par DP email: jiayiceline.leong@digipen.edu
\par Course: csd3450
\date 15-1-2024
\brief  Gameplay script for player interaction with items
****************************************************************************
***/

using ScriptAPI;
using System;

public class GallerySwitch : Script
{
    AudioComponent audioPlayer;

    public static bool isActivated = false;
    [SerializeField]
    public GameObject? _InteractUI;

    public override void Awake()
    {
        audioPlayer = gameObject.GetComponent<AudioComponent>();
    }

    public override void Start()
    {

    }

    public override void Update()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            Console.WriteLine("Gallery Switch");

            if (Input.GetKeyDown(Keycode.E))
            {
                isActivated = true;
                GalleryHiding.GhostShouldMove = true;

                if (GalleryLetter.isNotePicked)
                {
                    audioPlayer.play("pc_mighthaveopened");
                    GameplaySubtitles.counter = 43;
                }
                else
                {
                    audioPlayer.play("pc_openedsomething");
                    GameplaySubtitles.counter = 44;
                }

            }
        }
    }
}