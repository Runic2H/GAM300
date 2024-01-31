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
                ViewObject();
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
        if(Input.GetKeyDown(Keycode.M1))
        {
            Vector3 ObjectPos = gameObject.transform.GetPosition();
            Vector3 ObjectScale = gameObject.transform.GetScale();
            float mouseX = Input.GetLocalMousePosX();
            float mouseY = Input.GetLocalMousePosY();
            float minX = ObjectPos.X - ObjectScale.X * 0.5f;
            float maxX = ObjectPos.X + ObjectScale.X * 0.5f;
            float minY = ObjectPos.Y - ObjectScale.Y * 0.5f;
            float maxY = ObjectPos.Y + ObjectScale.Y * 0.5f;

            Console.WriteLine("MouseX: " + mouseX + " MinX: " + minX + " MaxX: " + maxX);
            Console.WriteLine("MouseY: " + mouseY + " MinY: " + minY + " MaxY: " + maxY);
            if (mouseX >= minX && mouseX <= maxX && mouseY >= minY && mouseY <= maxY)
                return true;
        }
        return false;
    }

    public void ViewObject()
    {
        if (storedObjName != "")
        {
            View_Object.ObjectName = storedObjName;
            View_Object.OnEnter = true;

            GameObjectScriptFind("ObjectViewer").SetActive(true);
            GameObjectScriptFind("InventoryObject").SetActive(false);
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
            }
            if(storedObjName == "???")
            {
                // Do ??? logic
            }
        }
    }
}