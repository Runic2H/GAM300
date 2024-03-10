/*!*************************************************************************
****
\file JumpscareScript.cs
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\par Course: csd3450
\date 9-2-2024
\brief  Script to toggle map
****************************************************************************
***/
using ScriptAPI;
using System;
using System.Numerics;

public class JumpscareScript : Script
{
    public GameBlackboard gameBlackboard;
    public GameObject player;
    public int jumpscareSequenceIndex;

    public override void Awake()
    {
        jumpscareSequenceIndex = 0;
        SetEnabled(false);
    }
    public override void Update()
    {
        switch (jumpscareSequenceIndex)
        {
            // 1. turn player camera towards ghost, then up fast
            case 0:

                // Turning towards ghost
                ScriptAPI.Vector3 line = gameObject.GetComponent<TransformComponent>().GetPosition() - player.GetComponent<TransformComponent>().GetPosition();


                break;

            // 2. (may want to add scream sounds here before next step)
            case 1:


                break;

            // 3. move ghost head down to player head (estimate) 
            case 2:


                break;

            // 4. lost screen
            case 3:

                SceneLoader.LoadLoseScreen();
                break;
        }
    }
}
