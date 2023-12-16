using ScriptAPI;
using System;

public class WASD : Script
{
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
        if (Input.GetKeyDown(Keycode.W))
        {
            gameObject.GetComponent<RigidBodyComponent>().SetLinearVelocity(new Vector3(1000, 0, 0));
        }
        else if (Input.GetKeyDown(Keycode.S))
        {
            gameObject.GetComponent<RigidBodyComponent>().SetLinearVelocity(new Vector3(-1000, 0, 0));
        }
        else
        {
            gameObject.GetComponent<RigidBodyComponent>().SetLinearVelocity(new Vector3(0, 0, 0));
        }
    }
    public override void LateUpdate()
    {

    }
    public override void OnDisable()
    {

    }
    public override void OnDestroy()
    {

    }
}