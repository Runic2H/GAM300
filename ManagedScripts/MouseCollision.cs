using ScriptAPI;
using System;

public class MouseCollision : Script
{
    public Vector2 boundingMin;
    public Vector2 boundingMax;
    public override void Awake()
    {

    }
    public override void OnEnable()
    {

    }
    public override void Start()
    {

    }
    public override void Update()
    {
        if (Input.GetMouseButtonDown(Keycode.M1))
        {
            CheckMouseCollision();
        }
    }

    private void CheckMouseCollision()
    {
        // C++ Input::GetLocalMousePos
        //Vector2 mousePosition = Input.mousePosition;

        //// Check if mouse is within the AABB
        //if (mousePosition.X >= boundingMin.X && mousePosition.X <= boundingMax.X &&
        //    mousePosition.Y >= boundingMin.Y && mousePosition.Y <= boundingMax.Y)
        //{
        //    Console.WriteLine("Mouse is within the AABB");
        //}
    }


}