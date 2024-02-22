/*!*************************************************************************
****
\file PopupUI.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 20-1-2024
\brief  Script for pause menu
****************************************************************************
***/
using ScriptAPI;
using System;

public class PopupUI : Script
{
    [SerializeField]
    public static bool isDisplayed = false;
    public bool lockpickDisplayed;
    UISpriteComponent popUpScreen;

    public GameObject player;

    public override void Awake()
    {
        lockpickDisplayed = false;
    }

    public override void Start()
    {
        popUpScreen = gameObject.GetComponent<UISpriteComponent>();
    }
    public override void Update()
    {

        if (Input.GetKeyDown(Keycode.ESC) || Input.GetKeyDown(Keycode.P))
        {
            isDisplayed = !isDisplayed;
        }

        if (isDisplayed)
        {
            //Console.WriteLine("game paused");
            popUpScreen.SetEnabled(true);
            Input.Lock(false);
            Input.HideMouse(false);
            //player.GetComponent<FPS_Controller_Script>().playerCanMove = false;
            //player.GetComponent<FPS_Controller_Script>().cameraCanMove = false;

        }
        else if(!InventoryScript.InventoryIsOpen && !lockpickDisplayed)
        {
            //Console.WriteLine("game unpaused");
            popUpScreen.SetEnabled(false);
            Input.Lock(true);
            Input.HideMouse(true);
            //player.GetComponent<FPS_Controller_Script>().playerCanMove = true;
            //player.GetComponent<FPS_Controller_Script>().cameraCanMove = true;
        }
    }

}
