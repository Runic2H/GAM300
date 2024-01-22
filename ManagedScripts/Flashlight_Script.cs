using ScriptAPI;
using System;

public class Flashlight_Script : Script
{
    //public Light lightSource;
    public float lightIntensity;
    public GameObject lightSourceObj;
    public bool activateLight = false;
    public GameDataManager myGameDataManager;
    public string flashAudiostr = "temp_flashlight";
    public AudioComponent flashAudio;                             

    [SerializeField] private bool flicker = false;
    [SerializeField] private float flickerTimer;

    public override void Awake()
    {
        flashAudio = gameObject.GetComponent<AudioComponent>();
    }

    public override void Update()
    {
        lightSourceObj = GameObjectScriptFind("Pointlight");
        lightIntensity = lightSourceObj.GetComponent<GraphicComponent>().getColourAlpha();

        //For Inspector Display Can Be Removed When Building
        //lightIntensity = lightSource.intensity;

        if (Input.GetKeyDown(Keycode.F))
        {
            activateLight = !activateLight;
            if (flashAudio.finished(flashAudiostr))
            {
                flashAudio.play(flashAudiostr);
            }
            if(activateLight == false)
            {
                lightSourceObj.GetComponent<GraphicComponent>().SetColourAlpha(0.0f);
            }
            else
            {
                lightSourceObj.GetComponent<GraphicComponent>().SetColourAlpha(0.6f);
            }
            //Input.KeyRelease(Keycode.F);
        }

        //Remove this chunck of code when building
        /*if (Input.GetKeyDown(Keycode.ZERO))
        {
            if (flicker)
            {
                flicker = false;
            }
            else
            {
                flicker = true;
            }
        }*/

        if (flicker)
        {
            FlickeringLight();
        }

        if (activateLight)
        {
            /*gameObject.GetComponent<MeshRenderer>().enabled = true;
            gameObject.GetComponent<CapsuleColliderComponent>().enabled = true;*/
            lightSourceObj.SetActive(true);
        }
        else
        {
           /* gameObject.GetComponent<MeshRenderer>().enabled = false;
            gameObject.GetComponent<CapsuleColliderComponent>().enabled = false;*/
            lightSourceObj.SetActive(false);
        }

        //BatteryLife();
    }

    public override void LateUpdate()
    {
        flashAudio.stop(flashAudiostr);
    }

    void BatteryLife()
    {
        if (lightIntensity <= 0)
        {
            activateLight = false;
            lightSourceObj.GetComponent<GraphicComponent>().SetColourAlpha(0.0f);
        }

        if (activateLight)
        {
            lightIntensity -= 0.0001f * Time.deltaTime;
        }
    }

    void FlickeringLight()
    {
        //This chunck of code is not right, by I like the result of the code so yea lul
        //if (flickerTimer >= 0)
        //{
        //    lightSource.enabled = true;
        //    flickerTimer -= 0.1f;
        //}
        //else if (flickerTimer <= 1)
        //{
        //    lightSource.enabled = false;
        //    flickerTimer += 0.1f;
        //}
    }
}
