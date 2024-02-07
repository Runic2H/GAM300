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
            interaction.SetActive(true);
        }
        else
        {
            interaction.SetActive(false);
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