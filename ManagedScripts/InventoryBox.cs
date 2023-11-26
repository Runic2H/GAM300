using ScriptAPI;
using System;
using static System.Net.Mime.MediaTypeNames;

public class InventoryBox : Script
{
    public string storedObjName;
    public ViewObject myViewObjScript;
    public InventoryScript myInventoryScript;
    public GameObject notesGrp;
    public GameObject itemsGrp;
    public GameObject paintingsGrp;
    //public Sprite emptyBox;

    public override void Awake()
    {
        //GetComponent<Button>().onClick.AddListener(AssignViewObjectString);
    }

    public override void Update()
    {
        if (storedObjName != "")
        {
            if(gameObject.GetNameTagComponent().GetTag() == "Note" && notesGrp.activeInHierarchy(notesGrp.GetEntityID()))
            {
                if(storedObjName != gameObject.GetComponent<UISpriteComponent>().GetTextureName())
                {
                    for (int i = 0; i < myInventoryScript.noteObjImg.Count; i++)
                    {
                        if (myInventoryScript.noteObjImg[i] == storedObjName)
                        {
                            gameObject.GetComponent<UISpriteComponent>().SetTextureName(myInventoryScript.noteObjImg[i]);
                            gameObject.GetComponent<Button>().interactable = true;                           
                            
                        }
                    }
                }
            }

            else if (gameObject.GetNameTagComponent().GetTag() == "Item" && itemsGrp.activeInHierarchy(itemsGrp.GetEntityID()))
            {
                if (storedObjName != gameObject.GetComponent<UISpriteComponent>().GetTextureName())
                {
                    for (int i = 0; i < myInventoryScript.itemObjImg.Count; i++)
                    {
                        if (myInventoryScript.itemObjImg[i] == storedObjName)
                        {
                            gameObject.GetComponent<UISpriteComponent>().SetTextureName(myInventoryScript.itemObjImg[i]);
                            gameObject.GetComponent<Button>().interactable = true;
                        }
                    }
                }
            }

            else if (gameObject.GetNameTagComponent().GetTag() == "Painting" && paintingsGrp.activeInHierarchy(paintingsGrp.GetEntityID()))
            {
                if (storedObjName != gameObject.GetComponent<UISpriteComponent>().GetTextureName())
                {
                    for (int i = 0; i < myInventoryScript.paintingsObjImg.Count; i++)
                    {
                        if (myInventoryScript.paintingsObjImg[i] == storedObjName)
                        {
                            gameObject.GetComponent<UISpriteComponent>().SetTextureName(myInventoryScript.paintingsObjImg[i]);
                            gameObject.GetComponent<Button>().interactable = true;
                        }
                    }
                }
            }
        }

        else if (storedObjName == "")
        {
            gameObject.GetComponent<Button>().interactable = false;
        }
    }

    public void AssignViewObjectString()
    {
        myViewObjScript.examineObject = storedObjName;
    }

    public void UseObject()
    {
        if (storedObjName == "Starting Battery" || storedObjName == "Toilet_Battery")
        {
            //myFlashlightScript.lightSource.intensity = 4;
            //myInventoryScript.inventoryAudioSource.clip = myInventoryScript.inventorySounds[0];
            //myInventoryScript.inventoryAudioSource.volume = 1;
            //myInventoryScript.inventoryAudioSource.Play();

            for (int i = 0; i < myInventoryScript.itemObjsInInventory.Count; i++)
            {
                if (myInventoryScript.itemObjsInInventory[i] == storedObjName)
                {
                    myInventoryScript.itemObjsInInventory[i] = "";
                    storedObjName = "";
                    //GetComponent<Button>().image.sprite = emptyBox;
                }
            }
        }
    }
}