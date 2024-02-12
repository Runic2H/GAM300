using ScriptAPI;
using System;

public class Flashlight_Script : Script
{
    //public Light lightSource;
    public GameObject lightSourceObj;
    public GameObject player;
    public bool activateLight = false;
    public GameDataManager myGameDataManager;
    public string flashAudiostr = "temp_flashlight";
    public AudioComponent flashAudio;
    public float followSpeed;
    public static int batteryLife = 100;
    public float batteryTick = 20.0f;

    private float tick = 0.0f;


    private Vector3 lookAmount = new Vector3();

    [SerializeField] private bool flicker = false;
    [SerializeField] private float flickerTimer;

    public override void Awake()
    {
        flashAudio = gameObject.GetComponent<AudioComponent>();
    }

    public override void Start()
    {
        if (lightSourceObj.GetComponent<SpotlightComponent>().GetEnabled())
        {
            Vector4 flashlightSettings = new Vector4(1f, 0.005f, 0.001f, 0.0f);
            lightSourceObj.GetComponent<SpotlightComponent>().SetAttenuation(flashlightSettings);
        }
    }

    public override void Update()
    {
        if (Input.GetKeyDown(Keycode.F))
        {
            activateLight = !activateLight;
            if (flashAudio.finished(flashAudiostr))
            {
                flashAudio.play(flashAudiostr);
            }
            //Input.KeyRelease(Keycode.F);
        }

        if (flicker)
        {
            FlickeringLight();
        }

        if (activateLight)
        {
            lightSourceObj.SetActive(true);
            BatteryLife();
        }
        else
        {
            lightSourceObj.SetActive(false);
        }

    }

    public override void LateUpdate()
    {
        flashAudio.stop(flashAudiostr);

        if (activateLight)
        {
            Vector3 currentDirection = new Vector3(lightSourceObj.GetComponent<SpotlightComponent>().GetDirection().X, lightSourceObj.GetComponent<SpotlightComponent>().GetDirection().Y, lightSourceObj.GetComponent<SpotlightComponent>().GetDirection().Z);
            Vector3 nextDirection = new Vector3(-player.GetComponent<FPS_Controller_Script>().playerCamera.transform.getForwardVector().X, -player.GetComponent<FPS_Controller_Script>().playerCamera.transform.getForwardVector().Y, player.GetComponent<FPS_Controller_Script>().playerCamera.transform.getForwardVector().Z);
            lookAmount = Vector3.MoveTowards(currentDirection, nextDirection, followSpeed * Time.deltaTime);

            Vector4 direction = new Vector4(lookAmount.X, lookAmount.Y, lookAmount.Z, 0.0f);
            lightSourceObj.GetComponent<SpotlightComponent>().SetDirection(direction);
            lightSourceObj.GetComponent<SpotlightComponent>().GetDirection().Normalize();

        }
    }

    void BatteryLife()
    {
        if (batteryLife <= 0)
        {
            activateLight = false;
        }

        if (activateLight)
        {
            tick += Time.deltaTime;
            if (tick >= batteryTick)
            {
                batteryLife--;
                Vector4 color = new Vector4(lightSourceObj.GetComponent<SpotlightComponent>().GetColor().X, lightSourceObj.GetComponent<SpotlightComponent>().GetColor().Y, lightSourceObj.GetComponent<SpotlightComponent>().GetColor().Z, lightSourceObj.GetComponent<SpotlightComponent>().GetColor().W * (batteryLife / 100.0f));
                lightSourceObj.GetComponent<SpotlightComponent>().SetColor(color);
                tick = 0.0f;
            }
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
