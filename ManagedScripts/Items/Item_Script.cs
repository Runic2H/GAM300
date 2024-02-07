using ScriptAPI;
using System;

public class Item_Script : Script
{
    private GameObject playerObject;

    [SerializeField]
    public string Item_Name;
    public string Item_Texture;

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
            Console.WriteLine("Picked up item");
            InventoryScript.addItemIntoInventory(Item_Name, Item_Texture);
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