using ScriptAPI;
using System;

public class Test : Script
{
    public override void Start()
    {
        Console.WriteLine("Start Test");
    }

    public override void Update()
    {
        //Console.WriteLine("Update");
        TransformComponent tf = GetTransformComponent();
        tf.SetPositionX(3.0f);
    }

    public override void OnDestroy() 
    {
        Console.WriteLine("Exit");
    }
}
