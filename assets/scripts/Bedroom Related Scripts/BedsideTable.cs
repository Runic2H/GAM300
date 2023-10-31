using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class BedsideTable : MonoBehaviour
{
    public bool collided;
    public GameObject _InteractUI;
    public ViewObject _ViewObjectScript;
    public GameObject object2View;
    bool interacted;

    [Header("Bedside Lamp Variables")]
    public Light tableLampLight;
    public Material NoEmission;
    public MeshRenderer tableLamp;

    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.E) && collided == true)
        {
            _InteractUI.SetActive(false);
            _ViewObjectScript.isExaming = true;
            _ViewObjectScript.examineObject = object2View.name;

            interacted = true;

            tableLampLight.enabled = false;
            tableLamp.material = NoEmission;
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.name == "Player" && interacted == false)
        {
            collided = true;
        }
    }

    private void OnCollisionExit(Collision collision)
    {
        collided = false;
    }
}
