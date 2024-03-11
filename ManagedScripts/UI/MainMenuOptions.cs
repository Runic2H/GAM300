/*!*************************************************************************
****
\file Mainmenuoption.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 25-3-2024
\brief  Script for options menu play button
****************************************************************************
***/
using ScriptAPI;
using System;

public class MainMenuOptions : Script
{
    private UISpriteComponent sprite;
    public AudioComponent mainmenubgm;
    public static bool isOpened;
    private AudioComponent buttonSfx;
    private string buttonSfxName = "";
    public override void Awake()
    {
        //GraphicsManagerWrapper.ToggleViewFrom2D(true);
        sprite = gameObject.GetComponent<UISpriteComponent>();
        buttonSfxName = "button_press";
        buttonSfx = gameObject.GetComponent<AudioComponent>();
    }

    public override void Start()
    {
        mainmenubgm = gameObject.GetComponent<AudioComponent>();
        
    }

    public override void Update()
    {
        if (Input.GetMouseButtonDown(Keycode.M1) && sprite.IsMouseCollided())
        {
            buttonSfx.play(buttonSfxName);
            isOpened = true;
            SceneLoader.LoadOptionsScreen();
        }
    }

    public override void OnDestroy()
    {

    }
}

