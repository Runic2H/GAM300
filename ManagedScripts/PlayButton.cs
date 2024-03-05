/*!*************************************************************************
****
\file playButton.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 22-11-2023
\brief  Script for main menu play button
****************************************************************************
***/
using ScriptAPI;
using System;

public class PlayButton : Script
{
    public AudioComponent bgm;
    public AudioSource audioPlayer;
    float temp_change;
    public string bgmName;
    private UISpriteComponent sprite;
    public GameObject blackScreen;
    private bool fading = false;
    private float incrementFading = Time.deltaTime / 3f;
    bool withinArea(float mouse, float min, float max)
    {
        bool within = false;
        if (mouse > min && mouse < max)
            within = true;
        return within;
    }

    public override void Awake()
    {
        GraphicsManagerWrapper.ToggleViewFrom2D(true);
        bgmName = "Horror_Menu_Finale_Finale";
        bgm = gameObject.GetComponent<AudioComponent>();
        audioPlayer = new AudioSource();
        sprite = gameObject.GetComponent<UISpriteComponent>();
    }

    public override void Start()
    {
        temp_change = 50f;
    }

    public override void Update()
    {
        if (bgm.finished(bgmName))
        {
            bgm.play(bgmName);
            //AudioSource.Play(bgmName);
        }

        if(Input.GetKeyDown(Keycode.V))
        {
            temp_change += 5f;
            bgm.setMasterVol(temp_change);
        }
        else if(Input.GetKeyDown(Keycode.B))
        {
            temp_change -= 5f;
            bgm.setMasterVol(temp_change);
        }
        Console.WriteLine(temp_change);

        if (Input.GetMouseButtonDown(Keycode.M1) && sprite.IsMouseCollided())
        {
            fading = true;
            bgm.FadeOut(3, bgmName);
            //GraphicsManagerWrapper.ToggleViewFrom2D(false);
        }
        if (fading == true)
        {
            float alpha = blackScreen.GetComponent<UISpriteComponent>().getColourAlpha();
            alpha += incrementFading;
            alpha = Mathf.Clamp(alpha, 0, 1);
            blackScreen.GetComponent<UISpriteComponent>().setColourAlpha(alpha);
            if (alpha >= 1)
            {
                fading = false;
                SceneLoader.LoadStartingCutscene();
            }
        }



    }

    public override void OnDestroy()
    {
        bgm.stop(bgmName);
    }
}
