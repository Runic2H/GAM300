﻿using ScriptAPI;
using System;

public class PlayButton : Script
{
    bool withinArea(float mouse, float min, float max)
    {
        bool within = false;
        if (mouse > min && mouse < max)
            within = true;
        return within;
    }

    bool withinButton(GameObject obj)
    {
        Vector3 ObjectPos = obj.GetComponent<TransformComponent>().GetPosition();//objectpos in ndc
        Vector3 ObjectScale = obj.GetComponent<TransformComponent>().GetScale();//obj scale in ndc
        float mouseX = Input.GetLocalMousePosX();
        float mouseY = Input.GetLocalMousePoxY();
        float minX = ObjectPos.X - ObjectScale.X / 2;
        float maxX = ObjectPos.X + ObjectScale.X / 2;
        float maxy = -ObjectPos.Y + ObjectScale.Y / 2;
        float miny = -ObjectPos.Y - ObjectScale.Y / 2;
        if (withinArea(mouseX, minX, maxX) && withinArea(mouseY, miny, maxy))
            return true;
        else
            return false;
    }
    public override void Awake()
    {
        GraphicsManagerWrapper.ToggleViewFrom2D(true);
    }

    public override void Update()
    {
        if (Input.GetMouseButtonDown(Keycode.M1) && withinButton(gameObject))
        {
            //GraphicsManagerWrapper.ToggleViewFrom2D(false);
            SceneLoader.LoadStartingCutscene();
        }
    }
}
