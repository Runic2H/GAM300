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

