using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class InventoryBoxScript : MonoBehaviour
{
    public string storedObjName;
    public ViewObject myViewObjScript;

    private void Start()
    {
        GetComponent<Button>().onClick.AddListener(AssignViewObjectString);
    }

    public void AssignViewObjectString()
    {
        myViewObjScript.examineObject = storedObjName;
    }
}
