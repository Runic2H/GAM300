/*!*************************************************************************
****
\file LostScript.cs
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\par Course: csd3450
\date 9-2-2024
\brief  Script when player is caught and loses game
****************************************************************************
***/
using ScriptAPI;
using System;

public class LostScript : Script 
{ 
	public override void Awake()
	{
		Input.Lock(false);
	}
	public override void Update()
	{
		for (int i = 0; i < 256; i++)
		{
			if (Input.GetKeyDown((char)i))
			{
                SceneLoader.LoadEndGameCredits();
            }
		}
	}
 }