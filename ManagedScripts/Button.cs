/*!*************************************************************************
****
\file Button.cs
\author Matthew Cheung
\par DP email: j.cheung@digipen.edu
\par Course: csd3450
\date 12-12-2023
\brief  Script for button logic
****************************************************************************
***/
using ScriptAPI;
using System;

//MouseCollision _MouseCollision;
public class Button : Script
{
    [SerializeField]
    public bool m_OnClick;
    
    [SerializeField]
    public bool interactable;
    public override void Awake()
    {
        GraphicsManagerWrapper.ToggleViewFrom2D(true);
    }

    public override void Update()
    {
        var entityID = gameObject.GetEntityID();
        if (Input.GetMouseButtonDown(Keycode.M1) && entityID == GraphicsManagerWrapper.GetPickedObject())
        {
            m_OnClick = true;

        }
    }

}

