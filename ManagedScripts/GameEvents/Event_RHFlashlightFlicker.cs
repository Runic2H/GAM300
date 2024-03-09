using ScriptAPI;
using System;

public class EventRHFlashlightFlicker : Script
{
    public bool doOnce = false;

    public override void Update()
    {

    }

    public override void OnTriggerEnter(ColliderComponent collider)
    {
        if (doOnce)
        {
            Flashlight_Script.batteryLife = 65.0f;
            doOnce = false;
            gameObject.GetComponent<ColliderComponent>().SetEnabled(false);
        }
    }
}