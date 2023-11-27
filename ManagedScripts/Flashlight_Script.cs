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

    private void Update()
    {
        //For Inspector Display Can Be Removed When Building
        //lightIntensity = lightSource.intensity;

        if (Input.GetKeyDown(Keycode.F) /*&& lightSource.intensity > 0*/)
        {
            if (activateLight)
            {
                activateLight = false;
            }
            else
            {
                activateLight = true;
            }
        }

        //Remove this chunck of code when building
        if (Input.GetKeyDown(Keycode.ZERO))
        {
            if (flicker)
            {
                flicker = false;
            }
            else
            {
                flicker = true;
            }
        }

        if (flicker)
        {
            FlickeringLight();
        }

        if (activateLight)
        {
            //gameObject.GetComponent<MeshRenderer>().enabled = true;
            //gameObject.GetComponent<CapsuleColliderComponent>().enabled = true;
            //lightSourceObj.SetActive(true);
        }
        else
        {
            //gameObject.GetComponent<MeshRenderer>().enabled = false;
            //gameObject.GetComponent<CapsuleColliderComponent>().enabled = false;
            //lightSourceObj.SetActive(false);
        }

        BatteryLife();
    }

    void BatteryLife()
    {
        //if (lightSource.intensity <= 0)
        //{
        //    activateLight = false;
        //    lightSource.intensity = 0;
        //}

        //if (activateLight)
        //{
        //    lightSource.intensity -= 0.01f * Time.deltaTime;
        //}
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
