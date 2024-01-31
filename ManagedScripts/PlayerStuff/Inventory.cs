using ScriptAPI;

public class InventoryScript : Script
{
    public GameObject InventoryObject;
    public View_Object _ViewObjectScript;

    public static List<string> noteObjsInInventory;
    public static List<string> itemObjsInInventory;
    public static List<string> paintingObjsInInventory;
    public static string currentTab;

    public static List<string> notesObjsImg;
    public static List<string> itemsObjsImg;
    public static List<string> paintingsObjsImg;

    public static bool InventoryIsOpen;

    //public Dictionary<string, string> ItemTexture;

    //buttons
    public GameObject ItemsTab;
    public GameObject NotesTab;
    public GameObject PaintingsTab;

    public override void Awake()
    {
        
    }

    public override void Start()
    {
        //Console.WriteLine("Initialising");
        initObjects();
    }

    public override void Update()
    {
        var entityID = gameObject.GetEntityID();

        if(Input.GetKeyDown(Keycode.I))
        {
            Console.WriteLine("I pressed");
            toggleInventory();
        }

        if (InventoryIsOpen) // Inventory opened
        {
            // Unhide and Unlock cursor here

            /* Commented for now because unhiding and unlocking cursor makes the game hang 
            //Input.Lock(false);
            //Input.HideMouse(true);  // For some reason visibility = hide ?
            */

            checkMouseInput();
        }
        else    // Inventory closed
        {
            // Hide and Lock cursor here
        }
    }

    public void toggleInventory()
    {
        Console.WriteLine("Toggle Inventory\n");
        InventoryIsOpen = !InventoryIsOpen;
        InventoryObject.SetActive(InventoryIsOpen);
    }

    public void checkMouseInput()
    {
        //Console.WriteLine("Checking Mouse Input\n");
        if (Input.GetMouseButtonDown(Keycode.M1))
        {
            Console.WriteLine("Mouse clicked");
            if(withinButton(ItemsTab)) // Slightly off in y-axis
            {
                Console.WriteLine("Collide Items\n");
                currentTab = "Items";
            }
            if(withinButton(NotesTab)) // Slightly off in y-axis
            {
                Console.WriteLine("Collide Notes\n");
                currentTab = "Notes";
            }
            if (withinButton(PaintingsTab)) // Slightly off in y-axis
            { 
                Console.WriteLine("Collide Paintings\n");
                currentTab = "Paintings";
            }
        }
    }

    public void initObjects()
    {
        Console.WriteLine("Init inventory objects\n");
        InventoryObject = GameObjectScriptFind("InventoryObject");

        ItemsTab        = GameObjectScriptFind("ItemsTab");
        NotesTab        = GameObjectScriptFind("NotesTab");
        PaintingsTab    = GameObjectScriptFind("PaintingsTab");

        itemsObjsImg = new List<string>
        {
            "Invnt Battery Img.dds",            "Inventory Box Img.dds",
            "Invnt Battery Img.dds",            "Inventory Box Img.dds",
            "Invnt Battery Img.dds",            "Inventory Box Img.dds",
            "Invnt Battery Img.dds",            "Inventory Box Img.dds",
            "Invnt Battery Img.dds",            "Inventory Box Img.dds",
            "Invnt Battery Img.dds",            "Inventory Box Img.dds"
        };

        itemObjsInInventory = new List<string>
        {
            "Battery",            "",
            "Battery",            "",
            "Battery",            "",
            "Battery",            "",
            "Battery",            "",
            "Battery",            ""
        };

        notesObjsImg = new List<string>
        {
            "Inventory Box Img.dds",            "Inventory Box Img.dds",
            "Inventory Box Img.dds",            "Inventory Box Img.dds",
            "Inventory Box Img.dds",            "Inventory Box Img.dds",
            "Notes7.dds",            "Notes8.dds",
            "Notes9.dds",            "Notes10.dds",
            "Notes11.dds",           "Notes12.dds"
        };

        noteObjsInInventory = new List<string>
        {
            "",           "",
            "",           "",
            "",           "",
            "Note7",           "Note8",
            "Note9",           "Note10",
            "Note11",           "Note12"
        };

        paintingsObjsImg = new List<string>
        {
            "Inventory Box Img.dds",            "Inventory Box Img.dds",
            "Inventory Box Img.dds",            "Inventory Box Img.dds",
            "Inventory Box Img.dds",            "Inventory Box Img.dds",
            "Inventory Box Img.dds",            "Inventory Box Img.dds",
            "Inventory Box Img.dds",            "Inventory Box Img.dds",
            "Inventory Box Img.dds",            "Inventory Box Img.dds"
        };

        paintingObjsInInventory = new List<string>
        {
            "",            "",
            "",            "",
            "",            "",
            "",            "",
            "",            "",
            "",            ""
        };

        InventoryObject.SetActive(false);
        InventoryIsOpen = false;
        currentTab = "Items";
    }

    public static void addPaintingIntoInventory(string painting_name, string texture_name)
    {
        Console.WriteLine("Adding painting " + texture_name);
        for (int i = 0; i < 12; ++i)
        {
            if (paintingObjsInInventory[i] == "" && paintingsObjsImg[i] == "Inventory Box Img.dds")
            {
                paintingObjsInInventory[i] = painting_name;
                paintingsObjsImg[i] = texture_name;
            }
        }
    }

    public static void addNoteIntoInventory(string note_name, string texture_name)
    {
        Console.WriteLine("Adding note " + texture_name);
        for (int i = 0; i < 12; ++i)
        {
            if (noteObjsInInventory[i] == "" && notesObjsImg[i] == "Inventory Box Img.dds")
            {
                noteObjsInInventory[i] = note_name;
                notesObjsImg[i] = texture_name;
            }
        }
    }

    public static void addItemIntoInventory(string item_name, string texture_name)
    {
        Console.WriteLine("Adding item " + texture_name);
        for(int i = 0; i < 12; ++i)
        {
            if (itemObjsInInventory[i] == "" && itemsObjsImg[i] == "Inventory Box Img.dds")
            {
                itemObjsInInventory[i] = item_name;
                itemsObjsImg[i] = texture_name;
            }
        }
    }
    
    bool withinButton(GameObject obj)
    {
        Vector3 ObjectPos = obj.transform.GetPosition();
        Vector3 ObjectScale = obj.transform.GetScale();
        float mouseX = Input.GetGlobalMousePosX();       // Need to change to UI coords... was using GetUIMousePos previously before the Input system got changed
        float mouseY = Input.GetGlobalMousePosY();       // Need to change to UI coords... was using GetUIMousePos previously before the Input system got changed
        float minX = ObjectPos.X - ObjectScale.X * 0.5f;
        float maxX = ObjectPos.X + ObjectScale.X * 0.5f;
        float minY = ObjectPos.Y - ObjectScale.Y * 0.5f;
        float maxY = ObjectPos.Y + ObjectScale.Y * 0.5f;

        Console.WriteLine("MouseX: " + mouseX + " MinX: " + minX + " MaxX: " + maxX);
        Console.WriteLine("MouseY: " + mouseY + " MinY: " + minY + " MaxY: " + maxY);
        if (mouseX >= minX && mouseX <= maxX && mouseY >= minY && mouseY <= maxY)
            return true;
        else
            return false;
    }
}
