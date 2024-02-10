using ScriptAPI;
using System;

public class PopupUI : Script
{
    [SerializeField]
    public static bool isDisplayed = false;
    UISpriteComponent popUpScreen;

    public override void Awake()
    {
    }

    public override void Start()
    {
        popUpScreen = gameObject.GetComponent<UISpriteComponent>();

    }
    public override void Update()
    {

        if (Input.GetKeyDown(Keycode.ESC))
        {
            isDisplayed = !isDisplayed;
        }

        if (isDisplayed)
        {
            //Console.WriteLine("game paused");
            GraphicsManagerWrapper.ToggleViewFrom2D(true);
            popUpScreen.SetEnabled(true);
            Input.Lock(false);
            Input.HideMouse(false);
        }
        else if(!InventoryScript.InventoryIsOpen && !isDisplayed)
        {
            //Console.WriteLine("game unpaused");
            GraphicsManagerWrapper.ToggleViewFrom2D(false);
            popUpScreen.SetEnabled(false);
            Input.Lock(true);
            Input.HideMouse(true);
        }
    }

}
