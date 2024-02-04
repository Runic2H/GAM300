using ScriptAPI;
using System;
using System.Diagnostics;

public class View_Object : Script
{
    GameObject ObjectViewer;
    GameObject ObjectViewerCam;
    GameObject ObjectViewerModel;
    
    //public static string ModelName;
    public static string ObjectName;
    public static bool OnEnter;
    public static bool isExamining;
    
    float root_y;
    float rotateValue;
    bool isZoomed;

    public override void Awake()
    {
    }

    public override void Start()
    {
        // MAKE SURE OBJECT THAT IS ATTACHED IS ACTIVE WHEN STARTING GAME
        Console.WriteLine("Init ObjectViewer\n");
        ObjectViewer        = GameObjectScriptFind("ObjectViewer");
        ObjectViewerCam     = GameObjectScriptFind("ObjectViewerCam");
        ObjectViewerModel   = GameObjectScriptFind("ObjectViewerModel");

        ObjectViewer.SetActive(false);
        gameObject.SetActive(false);

        //playercam = MainCam.GetComponent<CameraComponent>();
        ObjectViewerCam.GetComponent<CameraComponent>().SetFieldOfView(60f);

        OnEnter = false;
        isExamining = false;
        rotateValue = 0.0f;
        root_y = gameObject.transform.GetPosition().Y;
    }
    public override void Update()
    {
        if (OnEnter)
        {
            Console.WriteLine("On Enter");
            GameObjectScriptFind("InventoryObject").SetActive(false);
            InventoryScript.InventoryIsOpen = false;

            //ObjectViewerModel.GetComponent<GraphicComponent>().SetModelName(ObjectName); // Not working..

            isExamining = true;
            isZoomed = false;
            OnEnter = false;
        }
        
        if(isExamining)
        {
            Console.WriteLine("Examining");
            CheckMouseInput();
            CheckKeyboardInput();
            UpdateCamera();
        }
    }

    public void CheckKeyboardInput() // Keyboard Controls

    {
        //Console.WriteLine("Check Keyboard Input ViewObject");
        if (Input.GetKey(Keycode.A))
        {
            Console.WriteLine("A pressed");

            rotateValue += 0.01f;
            ObjectViewerModel.transform.SetRotation(new Vector3(0, rotateValue, 0));
        }
        else if (Input.GetKey(Keycode.D))
        {
            Console.WriteLine("D pressed");

            rotateValue -= 0.01f;
            ObjectViewerModel.transform.SetRotation(new Vector3(0, rotateValue, 0));
        }

        if (Input.GetKey(Keycode.S))
        {
            Console.WriteLine("S pressed");

            if (ObjectViewerModel.transform.GetPosition().Y > -1.0f)
            {
                root_y -= 0.01f;
                ObjectViewerModel.transform.SetPositionY(root_y);
            }
        }
        else if (Input.GetKey(Keycode.W))
        {
            Console.WriteLine("W pressed");

            if (ObjectViewerModel.transform.GetPosition().Y < 1.0f)
            {
                root_y += 0.01f;
                ObjectViewerModel.transform.SetPositionY(root_y);
            }
        }
    }

    public void CheckMouseInput()  // Mouse Controls
    {
        //Console.WriteLine("Check Mouse Input ViewObject");
        if (Input.GetMouseButtonDown(Keycode.M1)) //left click to zoom
        {
            Console.WriteLine("Left click pressed");

            isZoomed = !isZoomed;
        }
        if (Input.GetMouseButtonDown(Keycode.M2)) //right click to exit
        {
            Console.WriteLine("Right click pressed");

            isExamining = false;
            isZoomed = false;

            InventoryScript.InventoryIsOpen = true;
            GameObjectScriptFind("InventoryObject").SetActive(true);
            gameObject.SetActive(false);
        }
    }

    public void UpdateCamera()
    {
        Console.WriteLine("UpdateCam");

        if (isZoomed)
        {
            CameraComponent cam = ObjectViewerCam.GetComponent<CameraComponent>();
            ObjectViewerCam.GetComponent<CameraComponent>().SetFieldOfView(Mathf.Lerp(cam.GetFieldOfView(), 30, 30 * Time.deltaTime));
        }
        else
        {
            CameraComponent cam = ObjectViewerCam.GetComponent<CameraComponent>();
            ObjectViewerCam.GetComponent<CameraComponent>().SetFieldOfView(Mathf.Lerp(cam.GetFieldOfView(), 60, 5f * Time.deltaTime));
        }
    }
}