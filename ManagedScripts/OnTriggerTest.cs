using ScriptAPI;
using System;

public class OnTriggerTest : Script 
{ 
    public override void OnTriggerEnter(ColliderComponent collider)
    {
        Console.WriteLine("WOOHOOO");
        Console.WriteLine(collider.gameObject.GetComponent<NameTagComponent>().GetName());
    }
    public override void OnTriggerStay(ColliderComponent collider)
    {
        Console.WriteLine("STAYINGGG");
    }
    public override void OnTriggerExit(ColliderComponent collider)
    {
        Console.WriteLine("YEAHHHH");
    }
 }