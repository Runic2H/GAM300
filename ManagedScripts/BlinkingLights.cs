using ScriptAPI;
using System;


public class BlinkingLights : Script
{
    float OriginalIntensity;
    [SerializeField]
    public bool IsOn;
    [SerializeField]
    float timingcounter;
    [SerializeField]
    int flickercount;

    public string blinkinglightsound;
    public AudioComponent audio;

    public override void Awake()
    {
        IsOn = true;
        timingcounter = 0;
        OriginalIntensity = (float)gameObject.GetComponent<GraphicComponent>().getColourAlpha();
        flickercount = 0;
        blinkinglightsound = "lightshut2";
        audio = gameObject.GetComponent<AudioComponent>();
    }

    public override void Update()
    {
        //GameObjectScriptFind() use this to find the name of the sensor to turn of the light
        //Console.WriteLine(OriginalIntensity);
        //Console.WriteLine((float)gameObject.GetComponent<GraphicComponent>().getColourAlpha());
        timingcounter += Time.deltaTime;
        if (timingcounter > 1.0f)
        {
            IsOn = !IsOn;
            timingcounter = 0.0f;
            flickercount++;
        }

        if (flickercount > 15) 
            IsOn = false;

        if (!IsOn)
        {
            gameObject.GetComponent<GraphicComponent>().SetColourAlpha(0.0f);
        }
        else
        {
            gameObject.GetComponent<GraphicComponent>().SetColourAlpha(OriginalIntensity);
        }
    }
}