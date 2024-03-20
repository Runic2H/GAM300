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
    private bool isInteractUIActive = false;
    public override void Awake()
    {
        audioPlayer = gameObject.GetComponent<AudioComponent>();
    }

    public override void Start()
    {

    }

    public override void Update()
    {
        if (!isActivated && p02.isPaintingCollected && isInteractUIActive)
        {
            Console.WriteLine("Gallery Switch");
            //InteractUI.isShow = true;

            if (Input.GetKeyDown(Keycode.E))
            {
                isActivated = true;
                isInteractUIActive = false;
                GalleryHiding.GhostShouldMove = true;
                GalleryHiding.timeLimit = 10.0f;
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
        else
        {
            //_InteractUI.SetActive(false);
        }
        if (isInteractUIActive == false)
        {
            _InteractUI.SetActive(false);
        }

    }

    public override void OnTriggerEnter(ColliderComponent collider)
    {
        if (p02.isPaintingCollected)
        {
            isInteractUIActive = true;
            _InteractUI.SetActive(true);
        }

    }

    public override void OnTriggerExit(ColliderComponent collider)
    {
        isInteractUIActive = false;
        _InteractUI.SetActive(true);
    }
}