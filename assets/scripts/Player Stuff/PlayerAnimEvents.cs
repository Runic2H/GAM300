using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerAnimEvents : MonoBehaviour
{
    public Curtain_Trigger _Curtain_Trigger;

    public void EndOfPushBackAnim()
    {
        _Curtain_Trigger.completed = true;
    }
}
