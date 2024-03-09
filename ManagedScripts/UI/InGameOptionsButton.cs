/*!*************************************************************************
****
\file InGameOptionsButton.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 6-3-2024
\brief  Script for in game options button
****************************************************************************
***/
using System;
using ScriptAPI;

public class InGameOptionsButton : Script
{
    public GameBlackboard? gameBlackboard;
    UISpriteComponent optionsButtonSprite;
    public static bool openedOptionsMenu;

    public override void Awake()
    {
    }

    public override void Start()
    {
        optionsButtonSprite = gameObject.GetComponent<UISpriteComponent>();   
    }

    public override void Update()
    {
        if (gameBlackboard.gameState == GameBlackboard.GameState.Paused) //can be clicking when pause menu is open
        {
            optionsButtonSprite.SetEnabled(true);
        }
        else
        {
            optionsButtonSprite.SetEnabled(false);
        }

        if (Input.GetMouseButtonDown(Keycode.M1) && optionsButtonSprite.IsMouseCollided() && gameBlackboard.gameState == GameBlackboard.GameState.Paused)
        {
            Console.WriteLine("Options Button Pressed");
            AudioComponent audio = gameObject.GetComponent<AudioComponent>();
            audio.stopAll();
            openedOptionsMenu = true;
            gameBlackboard.gameState = GameBlackboard.GameState.Options;
            PopupUI.changeDisplayed = true;
        }
    }
}