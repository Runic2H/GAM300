using ScriptAPI;
using System;

public class EventBathroom : Script
{
    public GameObject? battery;

    public override void Update()
    {
        // Check for Battery pick up, play audio
        // Martin (Internal): At least this will help.
    }

    public override void OnTriggerEnter(ColliderComponent collider)
    {
        Console.WriteLine("Martin (Internal): The tub is still wet, but there’s no one...");
        gameObject.GetComponent<ColliderComponent>().SetEnabled(false);
    }
}