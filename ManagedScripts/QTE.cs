using ScriptAPI;
using System;

public class QTE : Script
{
    public bool isQTE = false;
    public GameObject interaction;
    public override void Awake()
    {
        interaction = GameObjectScriptFind("QTE for interaction");
    }
    public override void OnEnable()
    {

    }
    public override void Start()
    {
    }
    public override void Update()
    {
        if (gameObject.GetSphereColliderComponent().GetIsInteract())
        {
            isQTE = true;
        }
        else
        {
            isQTE = false;
            gameObject.GetSphereColliderComponent().SetIsInteract(false);
            gameObject.GetSphereColliderComponent().SetIsTrigger(false);
        }

        if (isQTE)
        {
            interaction.SetActive(interaction.GetEntityID(), true);
        }
        else
        {
            interaction.SetActive(interaction.GetEntityID(), false);
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