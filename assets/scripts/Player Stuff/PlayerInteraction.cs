using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerInteraction : MonoBehaviour
{
    private GameObject _Player;

    private void Start()
    {
        _Player = GameObject.Find("Player");
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.tag == "Door")
        {
            other.GetComponent<Door_Script>().collided = true;
            other.GetComponent<Door_Script>()._InteractUI.SetActive(true);
        }
        else if (other.tag == "Hideable")
        {
            if (other.GetComponent<Hiding>().hiding == false)
            {
                other.GetComponent<Hiding>().interactable = true;
                other.GetComponent<Hiding>()._InteractUI.SetActive(true);
            }
        }
        else if (other.name == "Bedroom_Bedside_Table's Trigger")
        {
            other.GetComponent<BedsideTable>().collided = true;
            other.GetComponent<BedsideTable>()._InteractUI.SetActive(true);
        }
        else if (other.name == "Painting_Open_Trigger")
        {
            other.GetComponent<PaintingTrigger_Script>().collided = true;
            other.GetComponent<PaintingTrigger_Script>()._InteractUI.SetActive(true);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "Door")
        {
            other.GetComponent<Door_Script>().collided = false;
            other.GetComponent<Door_Script>()._InteractUI.SetActive(false);
        }
        else if (other.tag == "Hideable")
        {
            if (other.GetComponent<Hiding>().hiding == false)
            {
                other.GetComponent<Hiding>().interactable = false;
                other.GetComponent<Hiding>()._InteractUI.SetActive(false);
            }
        }
        else if (other.name == "Bedroom_Bedside_Table's Trigger")
        {
            other.GetComponent<BedsideTable>().collided = false;
            other.GetComponent<BedsideTable>()._InteractUI.SetActive(false);
        }
        else if (other.name == "Painting_Open_Trigger")
        {
            other.GetComponent<PaintingTrigger_Script>().collided = false;
            other.GetComponent<PaintingTrigger_Script>()._InteractUI.SetActive(false);
        }
    }
}
