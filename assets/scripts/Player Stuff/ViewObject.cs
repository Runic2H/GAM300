using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ViewObject : MonoBehaviour
{
    public GameObject mainCam;
    public GameObject examineCam;
    public GameDataManager myGameDataManager;
    public Text added;
    public GameObject examineUI;
    public bool isExaming;
    public Transform[] viewableObjTransforms;

    Transform target;
    InventoryScript _Inventory;
    float root_y;
    float rotateValue;
    bool isZoomed;
    bool foundObj;

    [Header("Unique")]
    public string examineObject;
    public GameObject aboutText;

    [Header("AudioStuff")]
    public AudioSource playerVOSource;
    public AudioClip voClip;
    public Text subtitles;
    bool playedAudio;

    // Update is called once per frame
    private void Awake()
    {
        root_y = transform.position.y;
        _Inventory = GetComponent<InventoryScript>();
    }

    void Update()
    {
        if (isExaming)
        {
            mainCam.SetActive(false);
            examineCam.SetActive(true);
            GetComponent<FPS_Controller_Script>().playerCanMove = false;
            GetComponent<FPS_Controller_Script>().cameraCanMove = false;
            examineUI.SetActive(true);
            Cursor.visible = true;
            Cursor.lockState = CursorLockMode.None;

            if (!foundObj)
            {
                FindTarget();
            }
            else
            {
                #region Examine Controls
                if (Input.GetKey(KeyCode.A))
                {
                    rotateValue += 1;

                    target.eulerAngles = new Vector3(90, 180, rotateValue);
                }

                if (Input.GetKey(KeyCode.D))
                {
                    rotateValue -= 1;
                    target.eulerAngles = new Vector3(90, 180, rotateValue);
                }

                if (Input.GetKey(KeyCode.S))
                {
                    if (target.position.y > 0.4)
                    {
                        root_y -= 0.01f;
                        target.position = new Vector3(target.position.x, root_y, target.position.z);
                    }
                }

                if (Input.GetKey(KeyCode.W))
                {
                    if (target.position.y < 3.7)
                    {
                        root_y += 0.01f;
                        target.position = new Vector3(target.position.x, root_y, target.position.z);
                    }
                }

                if (Input.GetMouseButtonDown(0))
                {
                    if (!isZoomed)
                    {
                        isZoomed = true;
                    }
                    else
                    {
                        isZoomed = false;
                    }
                }

                if (isZoomed)
                {
                    examineCam.GetComponent<Camera>().fieldOfView = Mathf.Lerp(examineCam.GetComponent<Camera>().fieldOfView, 30, 30 * Time.deltaTime);
                }
                else if (!isZoomed)
                {
                    examineCam.GetComponent<Camera>().fieldOfView = Mathf.Lerp(examineCam.GetComponent<Camera>().fieldOfView, 60, 5f * Time.deltaTime);
                }
                #endregion
            }
        }

        if (isExaming && Input.GetMouseButtonDown(1))
        {
            if (target.gameObject.tag == "Note")
            {
                NoteInventoryCheck();
            }
            else if (target.gameObject.tag == "Item")
            {
                ItemInventoryCheck();
            }
            else if (target.gameObject.tag == "Painting")
            {
                PaintingInventoryCheck();
            }
        }
    }

    void FindTarget()
    {
       for (int x = 0; x < viewableObjTransforms.Length; x++)
        {
            if (examineObject == viewableObjTransforms[x].name)
            {
                target = viewableObjTransforms[x];
                target.gameObject.SetActive(true);
                foundObj = true;
            }
        }
    }

    #region Inventory Check
    void NoteInventoryCheck()
    {
        for (int x = 0; x < _Inventory.noteObjsInInventory.Count; x++)
        {
            if (_Inventory.noteObjsInInventory[x] == target.name.ToString())
            {
                GetComponent<FPS_Controller_Script>().playerCanMove = true;
                GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(false);
                examineCam.SetActive(false);
                mainCam.SetActive(true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(false);
                //examineObject.SetActive(false);
                target.gameObject.SetActive(false);
                Cursor.visible = false;
                Cursor.lockState = CursorLockMode.Locked;
            }
            else if (_Inventory.noteObjsInInventory[x] == "")
            {
                if (target.name == "Reciept")
                {
                    if (!playedAudio)
                    {
                        playerVOSource.clip = voClip;
                        playerVOSource.Play();
                        subtitles.enabled = true;
                        subtitles.text = "Martin (Internal): \"According to this, there�s a painting somewhere in here. But where?\"";
                        playedAudio = true;
                    }

                    if (!playerVOSource.isPlaying && playedAudio)
                    {
                        subtitles.enabled = false;
                        added.enabled = true;
                        _Inventory.noteObjsInInventory[x] = target.name.ToString();
                        GetComponent<FPS_Controller_Script>().playerCanMove = true;
                        GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                        examineCam.SetActive(false);
                        examineCam.SetActive(false);
                        mainCam.SetActive(true);
                        isExaming = false;
                        foundObj = false;
                        examineUI.SetActive(false);
                        //examineObject.SetActive(false);
                        target.gameObject.SetActive(false);
                        Cursor.visible = false;
                        Cursor.lockState = CursorLockMode.Locked;
                        break;
                    }
                }
                else
                {
                    added.enabled = true;
                    _Inventory.noteObjsInInventory[x] = target.name.ToString();
                    GetComponent<FPS_Controller_Script>().playerCanMove = true;
                    GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                    examineCam.SetActive(false);
                    examineCam.SetActive(false);
                    mainCam.SetActive(true);
                    isExaming = false;
                    foundObj = false;
                    examineUI.SetActive(false);
                    //examineObject.SetActive(false);
                    target.gameObject.SetActive(false);
                    this.enabled = false;
                    Cursor.visible = false;
                    Cursor.lockState = CursorLockMode.Locked;
                    break;
                }
            }
            else
            {
                Debug.LogError("No More Space");
            }
        }
    }

    void ItemInventoryCheck()
    {
        for (int x = 0; x < _Inventory.itemObjsInInventory.Count; x++)
        {
            if (_Inventory.itemObjsInInventory[x] == target.name.ToString())
            {
                GetComponent<FPS_Controller_Script>().playerCanMove = true;
                GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(false);
                examineCam.SetActive(false);
                mainCam.SetActive(true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(false);
                //examineObject.SetActive(false);
                target.gameObject.SetActive(false);
                Cursor.visible = false;
                Cursor.lockState = CursorLockMode.Locked;
            }
            else if (_Inventory.itemObjsInInventory[x] == "")
            {
                added.enabled = true;
                _Inventory.itemObjsInInventory[x] = target.name.ToString();
                GetComponent<FPS_Controller_Script>().playerCanMove = true;
                GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(false);
                examineCam.SetActive(false);
                mainCam.SetActive(true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(false);
                //examineObject.SetActive(false);
                target.gameObject.SetActive(false);
                Cursor.visible = false;
                Cursor.lockState = CursorLockMode.Locked;
                break;
            }
            else
            {
                Debug.LogError("No More Space");
            }
        }
    }

    void PaintingInventoryCheck()
    {
        for (int x = 0; x < _Inventory.paintingObjsInInventory.Count; x++)
        {
            if (_Inventory.paintingObjsInInventory[x] == target.name.ToString())
            {
                GetComponent<FPS_Controller_Script>().playerCanMove = true;
                GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(false);
                examineCam.SetActive(false);
                mainCam.SetActive(true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(false);
                //examineObject.SetActive(false);
                target.gameObject.SetActive(false);
                Cursor.visible = false;
                Cursor.lockState = CursorLockMode.Locked;
            }
            else if (_Inventory.paintingObjsInInventory[x] == "")
            {
                added.enabled = true;
                _Inventory.paintingObjsInInventory[x] = target.name.ToString();
                GetComponent<FPS_Controller_Script>().playerCanMove = true;
                GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(false);
                examineCam.SetActive(false);
                mainCam.SetActive(true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(false);
                //examineObject.SetActive(false);
                target.gameObject.SetActive(false);
                Cursor.visible = false;
                Cursor.lockState = CursorLockMode.Locked;
                break;
            }
            else
            {
                Debug.LogError("No More Space");
            }
        }
    }
    #endregion
}
