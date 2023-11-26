using ScriptAPI;
using System;

public class PlayButton : Script
{
    bool mouseonbutton;
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
    }

    public override void Update()
    {

        var entityID = gameObject.GetEntityID();
        Vector3 ObjectPos = gameObject.GetComponent<TransformComponent>().GetPosition();//objectpos in ndc
        Vector3 ObjectScale = gameObject.GetComponent<TransformComponent>().GetScale();
        float mouseX = Input.GetLocalMousePosX();
        float mouseY = Input.GetLocalMousePoxY();
        float minX = ObjectPos.X - ObjectScale.X;
        float maxX = ObjectPos.X + ObjectScale.X;
        float miny = ObjectPos.Y - ObjectScale.Y;
        float maxy = ObjectPos.Y + ObjectScale.Y;
        //Console.WriteLine(ObjectPos.X + "\t" + ObjectPos.Y + "\t" + ObjectPos.Z + "\n");
        Console.WriteLine("MinX: " + minX + "\t" + "MaxX: " + maxX + "\t" + "MouseX: " + mouseX + "\t");

        if (withinArea(mouseX, minX, maxX) && withinArea(mouseY, miny, maxy))
            mouseonbutton = true;
        else
            mouseonbutton = false;

        Console.WriteLine(mouseonbutton);
        if (Input.GetMouseButtonDown(Keycode.M1) && mouseonbutton)
        {
            //GraphicsManagerWrapper.ToggleViewFrom2D(false);
            SceneLoader.LoadStartingCutscene();
        }
    }
}
