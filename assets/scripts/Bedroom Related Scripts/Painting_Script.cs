using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Painting_Script : MonoBehaviour
{
    public Material _PaintingMaterial;
    public GameObject _OpenPaintingTrigger;
    public Animator _PaintingAnimator;
    public bool opened;
    public Flashlight_Script _FlashlightScript;
    private Color _color;
    [SerializeField] private bool collided;

    public InventoryScript _inventory;

    [Header("AudioStuff")]
    public AudioSource playerVOSource;
    public AudioClip[] voClip;
    public Text subtitles;
    public Image subtitlesBG;
    bool playedAudio;

    private void Start()
    {
        _color.a = 1;
    }

    // Update is called once per frame
    void Update()
    {
        if (collided == true && _color.a > 0.5f)
        {
            _color = _PaintingMaterial.color;
            _color.a -= 0.2f * Time.deltaTime;
            _PaintingMaterial.color = _color;
        }
        else if (collided == false && _color.a < 1f)
        {
            _color = _PaintingMaterial.color;
            _color.a += 0.5f * Time.deltaTime;
            _PaintingMaterial.color = _color;
        }

        if (!_FlashlightScript.activateLight)
        {
            collided = false;
        }

        if (_color.a <= 0.6f)
        {
            _OpenPaintingTrigger.SetActive(true);

            //checks if player has receipt, if so play a specific VO, else play another VO
            for (int x = 0; x < _inventory.noteObjsInInventory.Count; x++)
            {
                if (_inventory.noteObjsInInventory[x] != "Reciept")
                {
                    if (!playedAudio)
                    {
                        playerVOSource.clip = voClip[0];
                        playerVOSource.Play();
                        subtitles.enabled = true;
                        subtitlesBG.enabled = true;
                        subtitles.text = "Martin (Internal): \"Something’s behind this painting...\"";
                        playedAudio = true;
                    }

                    if (!playerVOSource.isPlaying && playedAudio)
                    {
                        subtitles.enabled = false;
                        subtitlesBG.enabled = false;
                        break;
                    }   
                }
                else if (_inventory.noteObjsInInventory[x] == "Reciept")
                {
                    if (!playedAudio)
                    {
                        playerVOSource.clip = voClip[1];
                        playerVOSource.Play();
                        subtitles.enabled = true;
                        subtitlesBG.enabled = true;
                        subtitles.text = "Martin (Internal): \"Looks like the receipt was right.\"";
                        playedAudio = true;
                    }

                    if (!playerVOSource.isPlaying && playedAudio)
                    {
                        subtitles.enabled = false;
                        subtitlesBG.enabled = false;
                        break;
                    }
                }
            }
                
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player's Light")
        {
            collided = true;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.gameObject.tag == "Player's Light")
        {
            collided = false;
        }
    }
}
