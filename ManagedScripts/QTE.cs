/*!*************************************************************************
****
\file QTE.cs
\author Cheang Wen Ding
\par DP email: cheang.w@digipen.edu
\par Course: csd3450
\date 25-11-2023
\brief  QTE Script
****************************************************************************
***/

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
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit() && gameObject.GetComponent<RigidBodyComponent>().IsPlayerCast())
        {
            interaction.SetActive(false);
        }
    }
    public override void LateUpdate()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit() && gameObject.GetComponent<RigidBodyComponent>().IsPlayerCast())
        {
            //Console.WriteLine(gameObject.GetComponent<NameTagComponent>().GetName());
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