/*!*************************************************************************
****
\file InteractUI.cs
\author Celine Leong
\par DP email: jiayiceline.leong@digipen.edu
\par Course: csd3450
\date 15-1-2024
\brief  Gameplay script for player interaction with paintings
****************************************************************************
***/
using Microsoft.VisualBasic;
using ScriptAPI;
using System;

public class InteractUI : Script
{

    override public void Awake()
    {
    }

    public override void Start()
    {
    }

    // Update is called once per frame
    override public void Update()
    {


    }

    public override void LateUpdate()
    {
        if (p01.isInteractable || p02.isInteractable || p03.isInteractable || p04.isInteractable
            || p05.isInteractable || p06.isInteractable || p07.isInteractable || GallerySwitch.isInteractable
            || GalleryLetter.isInteractable || Receipt.isInteractable)
        {
            gameObject.GetComponent<UISpriteComponent>().SetEnabled(true);
        }
        else
        {
            gameObject.GetComponent<UISpriteComponent>().SetEnabled(false);
        }
    }
}
