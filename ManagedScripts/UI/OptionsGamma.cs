/*!*************************************************************************
****
\file OptionsGamma.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 15-03-2024
\brief  Script for settings gamma in options menu
****************************************************************************
***/

using ScriptAPI;
using System;

public class OptionsGamma : Script
{
    public bool pressedGammaUp;
    private float gammaValue;
    private UISpriteComponent sprite;
    private AudioComponent buttonSfx;
    private string buttonSfxName = "";

    public GameObject gammaText;
    public override void Awake()
    {
        buttonSfxName = "button_press";
        buttonSfx = gameObject.GetComponent<AudioComponent>();
        sprite = gameObject.GetComponent<UISpriteComponent>();
    }

    public override void Update()
    {
        gammaValue = GraphicsManagerWrapper.GetFadeFactor();
        
        if (Input.GetMouseButtonDown(Keycode.M1) && sprite.IsMouseCollided())
        {
            if(pressedGammaUp)
            {
                gammaValue += 0.05f;
                GraphicsManagerWrapper.SetFadeFactor(gammaValue);
            }
            
            else
            {
                gammaValue -= 0.05f;
                GraphicsManagerWrapper.SetFadeFactor(gammaValue);
            }

            gammaValue = Math.Clamp(gammaValue, 0f, 1f);
            
            gammaText.GetComponent<UISpriteComponent>().SetFontMessage((Math.Round(gammaValue, 2)).ToString());
            buttonSfx.play(buttonSfxName);
        }

    }

    public override void OnDestroy()
    {
    }
}
