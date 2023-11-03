using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Added2InventTxtScript : MonoBehaviour
{
    public Text myText;

    // Update is called once per frame
    void Update()
    {
        if (myText.enabled)
        {
            Color _color = myText.color;
            _color.a -= 0.5f * Time.deltaTime;
            myText.color = _color;

            if (_color.a <= 0)
            {
                myText.enabled = false;
            }
        }
        else
        {
            Color _color = myText.color;
            _color.a = 1;
            myText.color = _color;
        }
    }
}
