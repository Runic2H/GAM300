using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.EventSystems;

public class InventoryScript : MonoBehaviour
{
    public GameObject _InventoryObj;
    public ViewObject _ViewObjectScript;
    public Button itemBttn;
    public Button notesBttn;
    public Button paintingsBttn;

    [Header("Inventory Parts")]
    public List<Sprite> noteObjImg;
    public List<string> noteObjsInInventory;
    public List<Button> noteButtons;
    public GameObject noteBttnGrp;

    public List<Sprite> itemObjImg;
    public List<string> itemObjsInInventory;
    public List<Button> itemButtons;
    public GameObject itemBttnGrp;

    public List<Sprite> paintingsObjImg;
    public List<string> paintingObjsInInventory;
    public List<Button> paintingButtons;
    public GameObject paintingBttnGrp;

    private void Start()
    {
        notesBttn.interactable = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (!_InventoryObj.activeInHierarchy)
        {
            if (Input.GetKeyDown(KeyCode.I))
            {
                _InventoryObj.SetActive(true);
                Cursor.visible = true;
                Cursor.lockState = CursorLockMode.None;
            }
        }
        else
        {
            if (Input.GetKeyDown(KeyCode.I))
            {
                _InventoryObj.SetActive(false);
                Cursor.visible = false;
                Cursor.lockState = CursorLockMode.Locked;
            }
        }
    }

    void ShowPaintingInInventory()
    {
        for (int x = 0; x < paintingObjsInInventory.Count; x++)
        {
            if (paintingObjsInInventory[x] == "Painting_1")
            {
                paintingButtons[x].image.sprite = paintingsObjImg[x];
            }
            else if (paintingObjsInInventory[x] == "Painting_2")
            {
                paintingButtons[x].image.sprite = paintingsObjImg[x];
            }
            else if (paintingObjsInInventory[x] == "Painting_3")
            {
                paintingButtons[x].image.sprite = paintingsObjImg[x];
            }
            else if (paintingObjsInInventory[x] == "Painting_4")
            {
                paintingButtons[x].image.sprite = paintingsObjImg[x];
            }
            else if (paintingObjsInInventory[x] == "Painting_5")
            {
                paintingButtons[x].image.sprite = paintingsObjImg[x];
            }
            else if (paintingObjsInInventory[x] == "Painting_6")
            {
                paintingButtons[x].image.sprite = paintingsObjImg[x];
            }
            else if (paintingObjsInInventory[x] == "Painting_7")
            {
                paintingButtons[x].image.sprite = paintingsObjImg[x];
            }
            else if (paintingObjsInInventory[x] == "Painting_8")
            {
                paintingButtons[x].image.sprite = paintingsObjImg[x];
            }
        }
    }

    void ShowNoteInInventory()
    {
        for (int x = 0; x < noteObjsInInventory.Count; x++)
        {
            if (noteObjsInInventory[x] != "")
            {
                if (noteButtons[x].GetComponent<InventoryBoxScript>().storedObjName == "")
                {
                    noteButtons[x].GetComponent<InventoryBoxScript>().storedObjName = noteObjsInInventory[x];
                }
            }
        }
    }

    public void ExamineObj()
    {
        _ViewObjectScript.enabled = true;
        _ViewObjectScript.isExaming = true;
        _InventoryObj.SetActive(false);
    }

    #region Click Header Bttns
    public void ClickItemBttn()
    {
        itemBttn.interactable = false;
        paintingsBttn.interactable = true;
        notesBttn.interactable = true;

        paintingBttnGrp.SetActive(false);
        itemBttnGrp.SetActive(true);
        noteBttnGrp.SetActive(false);
    }

    public void ClickPaintingBttn()
    {
        itemBttn.interactable = true;
        paintingsBttn.interactable = false;
        notesBttn.interactable = true;

        ShowPaintingInInventory();
        paintingBttnGrp.SetActive(true);
        itemBttnGrp.SetActive(false);
        noteBttnGrp.SetActive(false);
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
    }
    #endregion
}
