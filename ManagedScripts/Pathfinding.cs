/*!*************************************************************************
****
\file pathfinding.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 22-11-2023
\brief  Script for main menu play button
****************************************************************************
***/
using ScriptAPI;
using System;
using System.Runtime.InteropServices;

public class Pathfinding : Script 
{
	[SerializeField]
	public float stepTimer = 1.0f;
	public float currentStepTimer = 1.0f;

    public override void Awake()
	{
		Pathfinder.ReadLayoutFile("mansionLayout.txt");
		Pathfinder.SetTopLeft(new Vector2(-3573 + (125 / 2.0f), -1392 + (125 / 2.0f)));
		Pathfinder.SetGridSize(new Vector2(125, 125));

		Pathfinder.SetStart(1, 3);
		Pathfinder.SetGoal(5, 8);
    }
	public override void Update()
    {
        transform.SetPosition(new Vector3(6 * 125 + (-3573 + (125 / 2.0f)), transform.GetPosition().Y, 9 * 125 + (-1392 + (125 / 2.0f))));

  //      if (currentStepTimer <= 0)
		//{
  //          Vector2 nextStep = Pathfinder.GetNextStep();
		//	transform.SetPosition(new Vector3(nextStep.X, transform.GetPosition().Y, nextStep.Y));

  //          currentStepTimer = stepTimer;

  //      }
		//else 
		//{
  //          currentStepTimer -= Time.deltaTime;
  //      }
	}
 }