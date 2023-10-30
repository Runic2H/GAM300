using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MapScript : MonoBehaviour
{
    public GameObject _MapUI;
    bool displayMap;

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Tab))
        {
            if (displayMap)
            {
                _MapUI.SetActive(false);
                displayMap = false;
            }
            else if (!displayMap)
            {
                _MapUI.SetActive(true);
                displayMap = true;
            }
        }
    }
}
