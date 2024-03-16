﻿/*!*************************************************************************
****
\file Hiding.cs
\author Elton Teo Zhe Wei
\par DP email: e.teo@digipen.edu
\par Course: csd3450
\date 12-12-2023
\brief  Gameplay script for player hiding from the monster
****************************************************************************
***/
using System;
using System.Reflection.Emit;
using ScriptAPI;

public class EventBedroomHiding : Script
{
    public GameObject player;
    public GameObject enemyPathfinding;
    public GameObject closet;
    public bool hiding;
    [Header("AudioStuff")]
    //public AudioSource playerVOSource;
    public AudioComponent audioPlayer;  //#1
    String[] voClips;
    public String[] subtitles;

    public int numOfPaintingsTook = 0;


    public override void Update()
    {
        hiding = closet.GetComponent<Hiding>().hiding;
        if (hiding)
        {
            if (enemyPathfinding.GetComponent<GhostMovement>().bedroomHideEventDone == false && numOfPaintingsTook == 1) // triggering bedroom monster event 
            {
                if (enemyPathfinding.GetComponent<GhostMovement>().currentEvent != GhostMovement.GhostEvent.BedroomHidingEvent)
                {
                    enemyPathfinding.GetComponent<GhostMovement>().currentEvent = GhostMovement.GhostEvent.BedroomHidingEvent;
                    enemyPathfinding.GetComponent<GhostMovement>().startEvent = true;
                }
            }

            if (enemyPathfinding.GetComponent<GhostMovement>().bedroomHideEventDone)
            {
                audioPlayer.play(voClips[2]);
                GameplaySubtitles.counter = 15;
            }
        }
    }
}
