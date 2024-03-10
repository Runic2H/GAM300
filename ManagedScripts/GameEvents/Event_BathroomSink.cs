using ScriptAPI;
using System;

public class EventBathroomSink : Script
{
    public GameObject? battery;
    public bool doOnce = true;
    public GameObject? bathroomLights;
    public GameObject? bathroomCurtains;

    private bool flicker = false;
    public float flickerTimer = 0.0f;
    public float flickerSpeed = 1.0f;
    public bool flickerBool = true;

    public float flickerOffTimer = 1.0f;
    public bool showerEvent = false;

    public float showerCuratinMoveSpeed = 100.0f;

    public override void Update()
    {
        if (!battery.ActiveInHierarchy() && doOnce)
        {
            // Check for Battery pick up, play audio
            // Martin (Internal): At least this will help.
            flicker = true;
        }


        if(flicker)
        {
            doOnce = false;
            showerEvent = true;
            FlickeringLight();
            MoveShowerCurtain();
            flickerOffTimer -= Time.deltaTime;
            if(flickerOffTimer < 0.0f )
            {
                flicker = false;
                bathroomLights.SetActive(flicker);
                // Play light bulb exploding?
            }
        }
        if (showerEvent && !flicker) { 
            // Shower Curtain noise
            // Water stops running noise
        }
    }

    void FlickeringLight()
    {
        //This chunck of code is not right, by I like the result of the code so yea lul
        flickerTimer += Time.deltaTime;

        if (flickerTimer >= flickerSpeed)
        {
            flickerBool = !flickerBool;
            flickerTimer = 0.0f;
        }

        bathroomLights.SetActive(flickerBool);
    }

    void MoveShowerCurtain()
    {
        bathroomCurtains.transform.SetPositionX(bathroomCurtains.transform.GetPosition().X + (showerCuratinMoveSpeed * Time.deltaTime));
    }
}