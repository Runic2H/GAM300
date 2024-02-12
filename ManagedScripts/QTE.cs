using ScriptAPI;
using System;

public class QTE : Script
{

    public GameObject interaction;
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
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            interaction.SetActive(false);
        }
        
    }
    public override void LateUpdate()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit())
        {
            Console.WriteLine(gameObject.GetComponent<NameTagComponent>().GetName());
            interaction.SetActive(true);
        }
    }
    public override void OnDisable()
    {

    }
    public override void OnDestroy()
    {

    }
}