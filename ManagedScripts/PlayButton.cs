using ScriptAPI;
using System;

public class PlayButton : Script
{
    
    public override void Awake()
    {
         GraphicsManagerWrapper.ToggleViewFrom2D(true);
    }

    public override void Update()
    {
        
        var entityID = gameObject.GetEntityID();
        if (Input.GetMouseButtonDown(Keycode.M1) && entityID == GraphicsManagerWrapper.GetPickedObject())
        {
            //GraphicsManagerWrapper.ToggleViewFrom2D(false);
            SceneLoader.LoadStartingCutscene();
        }
    }
}
