/*!*************************************************************************
****
\file Note_Script.cs
\author Celine Leong
\par DP email: jiayiceline.leong@digipen.edu
\par Course: csd3450
\date 15-1-2024
\brief  Gameplay script for player interaction with notes
****************************************************************************
***/
using ScriptAPI;
using System;
using System.Threading.Tasks.Dataflow;

public class Note_Script : Script
{
    private GameObject playerObject;
    //RigidBodyComponent rigidBodyComponent; //for raycast?
    AudioComponent clip;
    AudioSource player;
    //bool once;
    String[] voClip;

    [SerializeField]
    public string Note_Name;
    public string Note_Texture;
    public string Note_VO;
    public GameObject? _InteractUI;

    public override void Awake()
    {
        Note_VO = "pc_checkreceipt";
        //once = true;
    }

    public override void Start()
    {
        playerObject = GameObjectScriptFind("player");
        //rigidBodyComponent = gameObject.GetComponent<RigidBodyComponent>();
        clip = gameObject.GetComponent<AudioComponent>();
        player = gameObject.GetComponent<AudioSource>();
    }

    public override void Update()
    {
        if (isWithinRange())
        {
            _InteractUI.SetActive(true);
            if (Input.GetKeyDown(Keycode.E) /*&& isWithinRange() && rigidBodyComponent.IsRayHit()*/) // Maybe add 1 more condition to check if its within player's view
            {
                //Console.WriteLine("Picked up note");
                InventoryScript.addNoteIntoInventory(Note_Name, Note_Texture);
                gameObject.GetComponent<GraphicComponent>().SetView2D(true);
                gameObject.SetActive(false);
                clip.play(Note_VO);
            }
        }
        else
        {
            _InteractUI.SetActive(false);
        }
    }

    public bool isWithinRange()
    {
        Vector3 itemPos = gameObject.transform.GetPosition();
        Vector3 playerPos = playerObject.transform.GetPosition();
        float distance = Vector3.Distance(itemPos, playerPos);
        //Console.WriteLine(distance);
        return distance < 100.0;
    }
}