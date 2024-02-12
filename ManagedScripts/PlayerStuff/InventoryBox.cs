using ScriptAPI;
using System;
using static System.Net.Mime.MediaTypeNames;

public class InventoryBox : Script
{
    [SerializeField]
    public int BoxNumber;
    public string storedObjName;
    public string storedObjTexture;

    //public Sprite emptyBox;

    public override void Awake()
    {
        //GetComponent<Button>().onClick.AddListener(AssignViewObjectString);
    }

    public override void Start()
    {
    }

    public override void Update()
    {
        DisplayItem();
        if(Clicked())
        {
            if(InventoryScript.currentTab == "Items")
            {
                UseObject();
            }
            else
            {
                //ViewObject();
            }
        }
    }

    public void DisplayItem()
    {
        if(InventoryScript.currentTab == "Items")
        {
            gameObject.GetComponent<UISpriteComponent>().SetTextureName(InventoryScript.itemsObjsImg[BoxNumber]);
            storedObjName = InventoryScript.itemObjsInInventory[BoxNumber];
            storedObjTexture = InventoryScript.itemsObjsImg[BoxNumber];
        }
        else if (InventoryScript.currentTab == "Paintings")
        {
            gameObject.GetComponent<UISpriteComponent>().SetTextureName(InventoryScript.paintingsObjsImg[BoxNumber]);
            storedObjName = InventoryScript.paintingObjsInInventory[BoxNumber];
            storedObjTexture = InventoryScript.paintingsObjsImg[BoxNumber];
        }
        else if (InventoryScript.currentTab == "Notes")
        {
            gameObject.GetComponent<UISpriteComponent>().SetTextureName(InventoryScript.notesObjsImg[BoxNumber]);
            storedObjName = InventoryScript.noteObjsInInventory[BoxNumber];
            storedObjTexture = InventoryScript.notesObjsImg[BoxNumber];
        }
    }

    public bool Clicked()
    {       
        return Input.GetKeyDown(Keycode.M1) && gameObject.GetComponent<UISpriteComponent>().IsMouseCollided();
    }

    public void ViewObject()
    {
        if (storedObjName != "")
        {
            View_Object.ObjectName = storedObjName;
            View_Object.OnEnter = true;
            GameObjectScriptFind("ObjectViewer").SetActive(true);
        }    
    }

    public void UseObject()
    {
        Console.WriteLine("Use Object");
        if(storedObjName != "")
        {
            InventoryScript.itemObjsInInventory[BoxNumber] = "";
            InventoryScript.itemsObjsImg[BoxNumber] = "Inventory Box Img.dds";

            // Do stuff based on what item is used
            if(storedObjName == "Battery")
            {
                // Do battery logic
                Flashlight_Script.batteryLife = 100;
            }
            if(storedObjName == "???")
            {
                // Do ??? logic
            }
        }
    }
}