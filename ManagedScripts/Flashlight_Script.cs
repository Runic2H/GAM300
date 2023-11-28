using ScriptAPI;
using System;

public class Flashlight_Script : Script
{
    //public Light lightSource;
    public float lightIntensity;
    public GameObject lightSourceObj;
    public bool activateLight = false;
    public GameDataManager myGameDataManager;

    [SerializeField] private bool flicker = false;
    [SerializeField] private float flickerTimer;

    public override void Update()
    {
        lightSourceObj = GameObjectScriptFind("Pointlight");
        lightIntensity = lightSourceObj.GetGraphicComponent().getColourAlpha();

        //For Inspector Display Can Be Removed When Building
        //lightIntensity = lightSource.intensity;

        if (Input.GetKeyDown(Keycode.F))
        {
            activateLight = !activateLight;
            if(activateLight == false)
            {
                lightSourceObj.GetGraphicComponent().SetColourAlpha(0.0f);
            }
            else
            {
                lightSourceObj.GetGraphicComponent().SetColourAlpha(0.3f);
            }
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
            lightSourceObj.SetActive(lightSourceObj.GetEntityID(),true);
        }
        else
        {
           /* gameObject.GetComponent<MeshRenderer>().enabled = false;
            gameObject.GetComponent<CapsuleColliderComponent>().enabled = false;*/
            lightSourceObj.SetActive(lightSourceObj.GetEntityID(),false);
        }

        //BatteryLife();
    }

    void BatteryLife()
    {
        if (lightIntensity <= 0)
        {
            activateLight = false;
            lightSourceObj.GetGraphicComponent().SetColourAlpha(0.0f);
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
