using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventFour_Script : MonoBehaviour
{
    public CheckGameState myGameState;
    bool collided;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "MainCamera")
        {
            collided = true;
            myGameState._CurrentState = GameState.Event4;
        }
    }
}
