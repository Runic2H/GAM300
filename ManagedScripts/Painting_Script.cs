using ScriptAPI;
using System;

public class Painting_Script : Script
{
    //public Material _PaintingMaterial;
    //public GameObject _OpenPaintingTrigger;
    public GameObject paintingParent;
    //public Animator _PaintingAnimator;
    public bool opened;
    //public Flashlight_Script _FlashlightScript;
    //private GraphicComponent _color;
    [SerializeField] private bool collided;

    //public InventoryScript _inventory;

    [Header("AudioStuff")]
    //public AudioSource playerVOSource;
    public string[] voClip;
    //public Text subtitles;
    //public Image subtitlesBG;
    bool playedAudio;

    public float timer;
    public bool receiptFound = false;
    public bool paintingTaken = false;

    override public void Awake()
    {
        voClip = new string[2];
        voClip[0] = "pc_shinelightbeforereceipt";
        voClip[1] = "pc_shinelightafterreceipt";
        //_color.a = 1;
        timer = 1.0f;
        Console.WriteLine("what");
        paintingTaken = false;
    }

    // Update is called once per frame
    override public void Update()
    {
        //if (collided == true && _color.getColourAlpha() > 0.5f)
        //{
            //_color = _PaintingMaterial.color;
            //_color.SetColourAlpha(_color.getColourAlpha() - 0.2f * Time.deltaTime);
            //_PaintingMaterial.color = _color;
        //}
        //else if (collided == false && _color.getColourAlpha() < 1f)
        //{
            //_color = _PaintingMaterial.color;
            //_color.SetColourAlpha(_color.getColourAlpha() + 0.5f * Time.deltaTime);
            //_PaintingMaterial.color = _color;
        //}

        //if (!_FlashlightScript.activateLight)
        //{
        //    collided = false;
        //}

        if (gameObject.GetComponent<SphereColliderComponent>().GetIsInteract()) // returns true if player is near it
        {
            if (timer <= 0.0f)
            {
                if (!receiptFound)
                {
                    Audio.play(voClip[0]);
                }
                else
                {
                    Audio.play(voClip[1]);
                }
            }
            else
            {
                timer -= Time.deltaTime;
            }

            if (Input.GetKeyDown(Keycode.E) && !paintingTaken && paintingParent.GetEntityID() != 0)
            {
                paintingParent.SetActive(paintingParent.GetEntityID(), false);
                paintingTaken = true;
            }
        }
        else
        {
            timer = 1.0f;
        }

        //if (_color.getColourAlpha() <= 0.6f)
        //{
            //_OpenPaintingTrigger.SetActive(_OpenPaintingTrigger.GetEntityID(), true);

            //checks if player has receipt, if so play a specific VO, else play another VO
            //for (int x = 0; x < _inventory.noteObjsInInventory.Count; x++)
            //{
            //    if (_inventory.noteObjsInInventory[x] != "Reciept")
            //    {
            //        if (!playedAudio)
            //        {
            //            //playerVOSource.clip = voClip[0];
            //            //playerVOSource.Play();
            //            //subtitles.enabled = true;
            //            //subtitlesBG.enabled = true;
            //            //subtitles.text = "Martin (Internal): \"Something�s behind this painting...\"";
            //            //playedAudio = true;
            //        }

            //        //if (!playerVOSource.isPlaying && playedAudio)
            //        //{
            //        //    subtitles.enabled = false;
            //        //    subtitlesBG.enabled = false;
            //        //    break;
            //        //}
            //    }
            //    else if (_inventory.noteObjsInInventory[x] == "Reciept")
            //    {
            //        if (!playedAudio)
            //        {
            //            //playerVOSource.clip = voClip[1];
            //            //playerVOSource.Play();
            //            //subtitles.enabled = true;
            //            //subtitlesBG.enabled = true;
            //            //subtitles.text = "Martin (Internal): \"Looks like the receipt was right.\"";
            //            //playedAudio = true;
            //        }

            //        //if (!playerVOSource.isPlaying && playedAudio)
            //        //{
            //        //    subtitles.enabled = false;
            //        //    subtitlesBG.enabled = false;
            //        //    break;
            //        //}
            //    }
            //}
        //}
    }

    //private void OnTriggerEnter(Collider other)
    //{
    //    if (other.gameObject.tag == "Player's Light")
    //    {
    //        collided = true;
    //    }
    //}

    //private void OnTriggerExit(Collider other)
    //{
    //    if (other.gameObject.tag == "Player's Light")
    //    {
    //        collided = false;
    //    }
    //}
}
