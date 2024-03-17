﻿/*!*************************************************************************
****
\file ReturnToGame.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 20-1-2024
\brief  Script for main menu quit game button
****************************************************************************
***/
using ScriptAPI;
using System;

public class QuitButton : Script
{
    public AudioComponent bgm;
    private UISpriteComponent sprite;
    private AudioComponent buttonSfx;
    private string buttonSfxName = "";

    public override void Awake()
    {
        sprite = gameObject.GetComponent<UISpriteComponent>();
        buttonSfxName = "button_press";
        buttonSfx = gameObject.GetComponent<AudioComponent>();
    }

    public override void Update()
    {
        if (Input.GetMouseButtonDown(Keycode.M1) && sprite.IsMouseCollided())
        {
            buttonSfx.play(buttonSfxName);
            AudioComponent audio = gameObject.GetComponent<AudioComponent>();
            //audio.stopAll();
            SceneLoader.LoadQuitGame();
        }
    }
}
