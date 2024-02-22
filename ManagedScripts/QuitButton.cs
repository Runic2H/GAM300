/*!*************************************************************************
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

    public override void Awake()
    {
       sprite = gameObject.GetComponent<UISpriteComponent>();
    }

    public override void Update()
    {
        if (Input.GetMouseButtonDown(Keycode.M1) && sprite.IsMouseCollided())
        {
            AudioComponent audio = gameObject.GetComponent<AudioComponent>();
            audio.stopAll();
            SceneLoader.LoadQuitGame();
        }
    }
}
