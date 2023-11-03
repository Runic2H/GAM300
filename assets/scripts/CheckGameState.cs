using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum GameState { Intro, LockpickTutorial, Gameplay, Event1, Event2, Event3, Event4}
public class CheckGameState : MonoBehaviour
{
    public GameState _CurrentState;
    public GameDataManager myGameDataManager;

    // Start is called before the first frame update
    void Start()
    {
 
    }

    // Update is called once per frame
    void Update()
    {

    }
}
