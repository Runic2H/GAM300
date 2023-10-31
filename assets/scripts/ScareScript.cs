using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ScareScript : MonoBehaviour
{

    public GameObject scareTest;

    // Start is called before the first frame update
    void Start()
    {
        scareTest.SetActive(false);
    }

    private void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.tag == "MainCamera")
        {
            scareTest.SetActive(true);
            Debug.Log("scareTest triggered");
        }
    }
}
