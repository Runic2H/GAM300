using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Bathtub_Interaction : MonoBehaviour
{
    public GameObject _InteractUI;
    public ViewObject _ViewObjectScript;
    public GameObject object2View;

    bool collided;
    bool interacted;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.E) && collided == true)
        {
            _InteractUI.SetActive(false);
            _ViewObjectScript.isExaming = true;
            _ViewObjectScript.examineObject = object2View.name;

            interacted = true;
        }
    }

    #region Collision Related
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "MainCamera" && !interacted)
        {
            collided = true;
            _InteractUI.SetActive(true);
        }
    }

    private void OnTriggerExit(Collider other)
    {
        _InteractUI.SetActive(false);
        collided = false;
    }
    #endregion
}
