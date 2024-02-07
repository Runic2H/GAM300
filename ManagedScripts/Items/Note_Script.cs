using ScriptAPI;
using System;

public class Note_Script : Script
{
    private GameObject playerObject;

    [SerializeField]
    public string Note_Name;
    public string Note_Texture;

    public override void Awake()
    {

    }

    public override void Start()
    {
        playerObject = GameObjectScriptFind("Player");
    }

    public override void Update()
    {
        if (Input.GetKeyDown(Keycode.E) && isWithinRange()) // Maybe add 1 more condition to check if its within player's view
        {
            Console.WriteLine("Picked up note");
            InventoryScript.addNoteIntoInventory(Note_Name, Note_Texture);
            gameObject.SetActive(false);
        }
    }

    public bool isWithinRange()
    {
        Vector3 itemPos = gameObject.transform.GetPosition();
        Vector3 playerPos = playerObject.transform.GetPosition();
        float distance = Vector3.Distance(itemPos, playerPos);
        Console.WriteLine(distance);
        return distance < 5.0;
    }
}