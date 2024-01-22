using ScriptAPI;

public class InventoryScript : Script
{
    public GameObject _InventoryObj;
    public ViewObject _ViewObjectScript;
    public Button itemBttn;
    public Button notesBttn;
    public Button paintingsBttn;
    //public Text examineOruseTxt;

    public List<string> noteObjsInInventory;
    public List<string> itemObjsInInventory;
    public List<string> paintingObjsInInventory;

    public List<Button> paintingButtons;
    public List<Button> noteButtons;
    public List<Button> itemButtons;

    public GameObject noteBttnGrp;
    public GameObject itemBttnGrp;
    public GameObject paintingBttnGrp;

    public List<string> noteObjImg;
    public List<string> itemObjImg;
    public List<string> paintingsObjImg;

    bool playedInventoryOpenClose;

    public override void Awake()
    {
        //notesBttn.interactable = false;
    }

    public override void Update()
    {
        var entityID = gameObject.GetEntityID();

        if (!_InventoryObj.ActiveInHierarchy())
        {
            if (Input.GetKeyDown(Keycode.I))
            {
                _InventoryObj.SetActive(true);
                //Cursor.visible = true;
                Cursor.LockState = CursorLockMode.None;

                if (!playedInventoryOpenClose)
                {
                    //audio here
                    playedInventoryOpenClose = true;
                }
            }
        }

        else
        {
            if (Input.GetKeyDown(Keycode.I))
            {
                _InventoryObj.SetActive(false);
                //Cursor.visible = false;
                Cursor.LockState = CursorLockMode.Locked;

                if (playedInventoryOpenClose && !_InventoryObj.ActiveInHierarchy())
                {
                    //audio here
                    playedInventoryOpenClose = false;
                }
            }
        }
    }
    public void ExamineObj()
    {
        _ViewObjectScript.OnDisable();
        _ViewObjectScript.isExaming = true;
        _InventoryObj.SetActive(false);
    }

    void ShowPaintingInInventory()
    {
        for (int x = 0; x < paintingObjsInInventory.Count; x++)
        {
            if (paintingObjsInInventory[x] != "")
            {
                if (paintingButtons[x].gameObject.GetComponent<InventoryBox>().storedObjName == "")
                {
                    paintingButtons[x].gameObject.GetComponent<InventoryBox>().storedObjName = paintingObjsInInventory[x];
                }
            }
        }
    }
    void ShowNoteInInventory()
    {
        for (int x = 0; x < noteObjsInInventory.Count; x++)
        {
            if (noteObjsInInventory[x] != "")
            {
                if (noteButtons[x].gameObject.GetComponent<InventoryBox>().storedObjName == "")
                {
                    noteButtons[x].gameObject.GetComponent<InventoryBox>().storedObjName = noteObjsInInventory[x];
                }
            }
        }
    }

    void ShowItemIninventory()
    {
        for (int x = 0; x < itemObjsInInventory.Count; x++)
        {
            if (itemObjsInInventory[x] != "")
            {
                if (itemButtons[x].gameObject.GetComponent<InventoryBox>().storedObjName == "")
                {
                    itemButtons[x].gameObject.GetComponent<InventoryBox>().storedObjName = itemObjsInInventory[x];
                }
            }
        }
    }

    public void ClickItemBttn()
    {
        itemBttn.interactable = false;
        paintingsBttn.interactable = true;
        notesBttn.interactable = true;

        paintingBttnGrp.SetActive(false);
        itemBttnGrp.SetActive(true);
        noteBttnGrp.SetActive(false);

        //examineOruseTxt.text = "Use";

        ShowItemIninventory();
    }

    public void ClickPaintingBttn()
    {
        itemBttn.interactable = true;
        paintingsBttn.interactable = false;
        notesBttn.interactable = true;

        paintingBttnGrp.SetActive( true);
        itemBttnGrp.SetActive(false);
        noteBttnGrp.SetActive(false);

        ShowPaintingInInventory();

        //examineOruseTxt.text = "Examine";
    }

    public void ClickNoteBttn()
    {
        itemBttn.interactable = true;
        paintingsBttn.interactable = true;
        notesBttn.interactable = false;

        paintingBttnGrp.SetActive(false);
        itemBttnGrp.SetActive(false);
        noteBttnGrp.SetActive(true);

        ShowNoteInInventory();

        //examineOruseTxt.text = "Examine";
    }
}


