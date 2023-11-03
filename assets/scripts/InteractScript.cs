using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InteractScript : MonoBehaviour
{
    public GameObject interactableObj;
    public Flashlight_Script myFL_Script;
    [SerializeField] private bool collidedWithInteractable;

    private void Update()
    {
        if (collidedWithInteractable)
        {
            if (Input.GetKeyDown(KeyCode.E))
            {
                if (interactableObj.name == "Battery")
                {
                    myFL_Script.lightSource.intensity = 3;
                    Destroy(interactableObj);
                    collidedWithInteractable = false;
                }
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Interactable"))
        {
            interactableObj = other.gameObject;
            collidedWithInteractable = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Interactable"))
        {
            interactableObj = null;
            collidedWithInteractable = false;
        }
    }
}
