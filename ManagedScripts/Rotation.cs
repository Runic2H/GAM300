using ScriptAPI;
using System;

public class Rotation : Script
{
    private float rotationSpeed = 45.0f;
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
        float yRotation = rotationSpeed * Time.deltaTime;
        Vector3 rot_Vec3 = new Vector3(0, yRotation, 0);
        Quaternion rotation = Quaternion.Euler(rot_Vec3);
        //gameObject.GetComponent<RigidBodyComponent>().SetRotation(rotation);
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