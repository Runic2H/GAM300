using ScriptAPI;
using System;

public class Painting_Script : Script
{
    private GameObject playerObject;

    [SerializeField]
    public string Painting_Name;
    public string Painting_Texture;
    public bool opened;
    private bool collided;

    //public Animator _PaintingAnimator;
    //public Flashlight_Script _FlashlightScript;
    //private GraphicComponent _color;

    [Header("AudioStuff")]
    public AudioSource AudioPlayer;
    public AudioComponent[] voClip = new AudioComponent[2];

    public float timer;

    override public void Awake()
    {
        voClip[0].setFilePath("pc_stealpainting1");
        voClip[1].setFilePath("pc_shinelightafterreceipt"); //This one should be items VO
        //_color.a = 1;
        timer = 1.0f;
        Console.WriteLine("Painting script");
    }

    public override void Start()
    {
        playerObject = GameObjectScriptFind("Player");
    }

    // Update is called once per frame
    override public void Update()
    {
        if (Input.GetKeyDown(Keycode.E) && isWithinRange()) // Maybe add 1 more condition to check if its within player's view
        {
            Console.WriteLine("Picked up painting");
            InventoryScript.addPaintingIntoInventory(Painting_Name, Painting_Texture);
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
