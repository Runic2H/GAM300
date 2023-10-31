using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class Curtain_Trigger : MonoBehaviour
{
    public GameObject _InteractUI;
    public GameObject enemyObj;
    public EventToilet_Script myToiletEvent;
    public FPS_Controller_Script playerController;
    public BoxCollider myShowerKnobCollider;
    public BoxCollider bathtubCollider;
    public Animator playerAnimator;
    public bool completed;

    [Header("QTE UI Elements")]
    public GameObject _qteUI;
    public Image radialProgressBar;

    [SerializeField] float disappearDelay = 0f;
    bool collided;
    Animator _CurtainAnimator;

    private void Start()
    {
        _CurtainAnimator = GetComponent<Animator>();
    }

    // Update is called once per frame
    void Update()
    {
        if (collided && Input.GetKeyDown(KeyCode.E))
        {
            _CurtainAnimator.SetBool("Open", true);

            _InteractUI.SetActive(false);

            myShowerKnobCollider.enabled = true;

            gameObject.GetComponent<BoxCollider>().enabled = false;

            playerController.playerCanMove = false;
        }

        if (_CurtainAnimator.GetBool("Open"))
        {
            if (_CurtainAnimator.GetCurrentAnimatorStateInfo(0).length < _CurtainAnimator.GetCurrentAnimatorStateInfo(0).normalizedTime)
            {
                playerAnimator.enabled = true;

                if (playerAnimator.GetCurrentAnimatorStateInfo(0).IsName("DunkInWaterLoopAnimation"))
                {
                    _qteUI.SetActive(true);

                    if (Input.GetKeyDown(KeyCode.E) && radialProgressBar.fillAmount < 1)
                    {
                        radialProgressBar.fillAmount += 0.03f;
                    }
                    else if (radialProgressBar.fillAmount >= 1)
                    {
                        playerAnimator.SetBool("Toilet_Success", true);
                        
                        _qteUI.SetActive(false);
                    }
                }
                else if (playerAnimator.GetCurrentAnimatorStateInfo(0).IsName("Push_Back"))
                {
                    if (disappearDelay >= 1f)
                    {
                        Destroy(enemyObj);
                    }
                    else
                    {
                        disappearDelay += Time.deltaTime;
                    }
                }
            }
        }

        if (completed)
        {
            this.enabled = false;
            playerAnimator.enabled = false;
            bathtubCollider.enabled = true;
            playerController.playerCanMove = true;
            bathtubCollider.enabled = true;
        }
    }

    #region Collision Related
    private void OnTriggerEnter(Collider other)
    {
        collided = true;
        _InteractUI.SetActive(true);
    }

    private void OnTriggerExit(Collider other)
    {
        collided = false;
        _InteractUI.SetActive(false);
    }
    #endregion
}
