using ScriptAPI;
using System;
using System.Diagnostics;

public class ViewObject : Script
{
    GameObject mainCam;
    GameObject examineCam;
    //public GameDataManager myGameDataManager;
    //public Text added;
    public GameObject examineUI;
    public bool isExaming;

    TransformComponent[] viewableObjTransforms;    //public Transform[] viewableObjTransforms;
    TransformComponent target;                     //transform
    InventoryScript _Inventory;
    
    public string examineObject;
    float root_y;
    float rotateValue;
    bool isZoomed;
    bool foundObj;
    bool exiting;

    public override void Awake()
    {
        root_y = gameObject.transform.GetPosition().Y;
        _Inventory = gameObject.GetComponent<InventoryScript>();
    }
    public override void Update()
    {
        var mainCamID = mainCam.GetEntityID();
        var examineCamID = examineCam.GetEntityID();
        var examineUIID = examineUI.GetEntityID();
        
        if (isExaming)
        {
            mainCam.SetActive(mainCamID, false);
            examineCam.SetActive(examineCamID, true);
            gameObject.GetComponent<FPS_Controller_Script>().playerCanMove = false;
            gameObject.GetComponent<FPS_Controller_Script>().cameraCanMove = false;
            examineUI.SetActive(examineUIID, true);
            //Cursor.visible = true;
            Cursor.LockState = CursorLockMode.None;

            if (!foundObj)
            {
                FindTarget();
            }
            else
            {
                #region Examine Controls
                if (Input.GetKey(Keycode.A))
                {
                    rotateValue += 1;
                    
                   if(target.gameObject.GetComponent<NameTagComponent>().GetTag() == "Painting")
                    {
                        //eulerAngles
                        target.SetRotation(new Vector3(0, rotateValue, 0));
                    }
                    
                    else
                    {
                        target.SetRotation(new Vector3(90, 180, rotateValue));
                    }
                }

                if (Input.GetKey(Keycode.D))
                {
                    rotateValue -= 1;

                    if (target.gameObject.GetComponent<NameTagComponent>().GetTag() == "Painting")
                    {
                        target.SetRotation(new Vector3(0, rotateValue, 0));
                    }
                    else
                    {
                        target.SetRotation(new Vector3(90, 180, rotateValue));
                    }
                }

                if (Input.GetKey(Keycode.S))
                {
                    if(target.GetPosition().Y > 0.4)
                    {
                        root_y -= 0.01f;
                        target.SetPosition(new Vector3(target.GetPosition().X, root_y, target.GetPosition().Z));
                    }
                }

                if (Input.GetKey(Keycode.W))
                {
                    if(target.GetPosition().Y < 3.7)
                    {
                        root_y += 0.01f;
                        target.SetPosition(new Vector3(target.GetPosition().X, root_y, target.GetPosition().Z));
                    }
                }

                if (Input.GetMouseButtonDown(Keycode.M1)) //left click
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
                    examineCam.GetComponent<CameraComponent>().SetFieldOfView(Mathf.Lerp(examineCam.GetComponent<CameraComponent>().GetFieldOfView(), 30, 30 * Time.deltaTime));
                }
                else if (!isZoomed)
                {
                    examineCam.GetComponent<CameraComponent>().SetFieldOfView(Mathf.Lerp(examineCam.GetComponent<CameraComponent>().GetFieldOfView(), 60, 5f * Time.deltaTime));
                }
                #endregion
            }
        }
        if (isExaming && Input.GetMouseButtonDown(Keycode.M2))
        {
            exiting = true;
        }

        if (exiting)
        {
            if(target.gameObject.GetComponent<NameTagComponent>().GetTag() == "Note")
            {
                NoteInventoryCheck();
            }
            else if (target.gameObject.GetComponent<NameTagComponent>().GetTag() == "Item")
            {
                ItemInventoryCheck();
            }
            else if (target.gameObject.GetComponent<NameTagComponent>().GetTag() == "Painting")
            {
                PaintingInventoryCheck();
            }
        }
    }
    void FindTarget()
    {
        for (int x = 0; x < viewableObjTransforms.Length; x++)
        {
            if(examineObject == viewableObjTransforms[x].gameObject.GetNameTagComponent().GetName())
            {
                target = viewableObjTransforms[x];
                target.gameObject.SetActive(target.gameObject.GetEntityID(), true);
                foundObj = true;
            }
        }
    }

    void NoteInventoryCheck()
    {
        for (int x = 0; x < _Inventory.noteObjsInInventory.Count; x++)
        {
            if(_Inventory.noteObjsInInventory[x] == target.gameObject.GetNameTagComponent().GetName())
            {
                gameObject.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                gameObject.GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(examineCam.GetEntityID(), false);
                mainCam.SetActive(mainCam.GetEntityID(), true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(examineUI.GetEntityID(), false);
                target.gameObject.SetActive(target.gameObject.GetEntityID(), false);
                Cursor.LockState = CursorLockMode.Locked;
                exiting = false;
                break;
            }

            else if(_Inventory.noteObjsInInventory[x] == "")
            {
                if(target.gameObject.GetNameTagComponent().GetName() == "Reciept")
                {
            //        if (!playedAudio)
            //        {
            //            playerVOSource.clip = voClip;
            //            playerVOSource.Play();
            //            subtitles.enabled = true;
            //            subtitles.text = "Martin (Internal): \"According to this, there’s a painting somewhere in here. But where?\"";
            //            playedAudio = true;
            //            isExaming = false;
            //            examineUI.SetActive(false);
            //        }

            //        if (!playerVOSource.isPlaying && playedAudio)
            //        {
            //            subtitles.enabled = false;
            //            added.enabled = true;
            //            _Inventory.noteObjsInInventory[x] = target.name.ToString();
            //            GetComponent<FPS_Controller_Script>().playerCanMove = true;
            //            GetComponent<FPS_Controller_Script>().cameraCanMove = true;
            //            examineCam.SetActive(false);
            //            examineCam.SetActive(false);
            //            mainCam.SetActive(true);
            //            isExaming = false;
            //            foundObj = false;
            //            examineUI.SetActive(false);
            //            target.gameObject.SetActive(false);
            //            Cursor.visible = false;
            //            Cursor.lockState = CursorLockMode.Locked;
            //            exiting = false;
            //            break;
            //        }
                }
                else
                {
                    //subtitles.enabled = false;
                    //added.enabled = true;
                    _Inventory.noteObjsInInventory[x] = target.gameObject.GetNameTagComponent().GetName();
                    gameObject.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                    gameObject.GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                    examineCam.SetActive(examineCam.GetEntityID(), false);
                    mainCam.SetActive(mainCam.GetEntityID(), true);
                    isExaming = false;
                    foundObj = false;
                    examineUI.SetActive(examineUI.GetEntityID(), false);
                    target.gameObject.SetActive(target.gameObject.GetEntityID(), false);
                    Cursor.LockState = CursorLockMode.Locked;
                    //this.enabled = false;
                    exiting = false;
                    break;
                }
            }

            else
            {
                Debug.WriteLine("No More Space"); // Debug.LogError
            }
        }
    }

    void ItemInventoryCheck()
    {
        for (int x = 0; x < _Inventory.itemObjsInInventory.Count; x++)
        {
            if(_Inventory.itemObjsInInventory[x] == target.gameObject.GetNameTagComponent().GetName())
            {
                gameObject.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                gameObject.GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(examineCam.GetEntityID(), false);
                mainCam.SetActive(mainCam.GetEntityID(), true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(examineUI.GetEntityID(), false);
                target.gameObject.SetActive(target.gameObject.GetEntityID(), false);
                Cursor.LockState = CursorLockMode.Locked;
                exiting = false;
                break;
            }

            else if (_Inventory.itemObjsInInventory[x] == "")
            {
                //added.enabled = true;
                _Inventory.itemObjsInInventory[x] = target.gameObject.GetNameTagComponent().GetName();
                gameObject.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                gameObject.GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(examineCam.GetEntityID(), false);
                mainCam.SetActive(mainCam.GetEntityID(), true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(examineUI.GetEntityID(), false);
                target.gameObject.SetActive(target.gameObject.GetEntityID(), false);
                Cursor.LockState = CursorLockMode.Locked;
                //Cursor.visible = false;
                exiting = false;
                break;
            }
            else
            {
                Debug.WriteLine("No More Space"); // Debug.LogError
            }
        }
    }

    void PaintingInventoryCheck()
    {
        for (int x = 0; x < _Inventory.paintingObjsInInventory.Count; x++)
        {
            if(_Inventory.paintingObjsInInventory[x] == target.gameObject.GetNameTagComponent().GetName())
            {
                gameObject.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                gameObject.GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(examineCam.GetEntityID(), false);
                mainCam.SetActive(mainCam.GetEntityID(), true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(examineUI.GetEntityID(), false);
                target.gameObject.SetActive(target.gameObject.GetEntityID(), false);
                //Cursor.visible = false;
                Cursor.LockState = CursorLockMode.Locked;
                exiting= false;
                break;

            }

            else if (_Inventory.paintingObjsInInventory[x] == "")
            {
                //added.enabled = true;
                _Inventory.paintingObjsInInventory[x] = target.gameObject.GetNameTagComponent().GetName();
                gameObject.GetComponent<FPS_Controller_Script>().playerCanMove = true;
                gameObject.GetComponent<FPS_Controller_Script>().cameraCanMove = true;
                examineCam.SetActive(examineCam.GetEntityID(), false);
                mainCam.SetActive(mainCam.GetEntityID(), true);
                isExaming = false;
                foundObj = false;
                examineUI.SetActive(examineUI.GetEntityID(), false);
                target.gameObject.SetActive(target.gameObject.GetEntityID(), false);
                //Cursor.visible = false;
                Cursor.LockState = CursorLockMode.Locked;
                exiting = false;
                break;
            }
            else
            {
                Debug.WriteLine("No More Space"); // Debug.LogError
            }
        }
    }

}