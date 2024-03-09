﻿using ScriptAPI;
using System;

public class FinishGame : Script
{
    //.public GameObject interactUI;
    private bool interact;

    private bool fadeOut = false;
    private float fadeValueIncrement = 0.05f;

    public GameObject doorStates;
    public GameObject doorText;
    public GameBlackboard blackboard;

    readonly string climbingSFX = "end_climbing";
    AudioComponent audio;

    public override void Awake()
    {
        doorText = GameObjectScriptFind("DoorText");    // Hate this please change after milestone
        blackboard = GameObjectScriptFind("GameBlackboard").GetComponent<GameBlackboard>();    // Hate this please change after milestone
        audio = gameObject.GetComponent<AudioComponent>();
    }
    public override void Start()
    {

    }
    public override void Update()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            doorStates.GetComponent<DoorState>().doorLookedAt = true;
            doorText.GetComponent<UISpriteComponent>().SetFontMessage("Press E to Interact");

            if (Input.GetKeyDown(Keycode.E) || fadeOut == true)
            {
                fadeOut = true;
                float fadeValue = GraphicsManagerWrapper.GetFadeFactor();
                if (fadeOut == true)
                {
                    fadeValue -= fadeValueIncrement;
                    GraphicsManagerWrapper.SetFadeFactor(fadeValue);
                    audio.play(climbingSFX);
                    audio.FadeOut(2, climbingSFX);
                    if (fadeValue <= 0.0f)
                    {
                        fadeOut = false;
                        Input.Lock(false);
                        Input.HideMouse(false);
                        SceneLoader.LoadTempEndScene();
                    }
                }
            }
        }
    }
    public override void LateUpdate()
    {

    }

}
