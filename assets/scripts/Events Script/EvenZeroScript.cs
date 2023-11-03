using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EvenZeroScript : MonoBehaviour
{
    public GameObject mainDoor;
    public AudioSource voSource;
    public AudioClip[] eventAudio;

    bool collided;
    bool played;

    private void Update()
    {
        if (collided)
        {
            mainDoor.GetComponent<Door_Script>().doorAnimator.SetBool("Open", false);
            mainDoor.GetComponent<Door_Script>().doorState = 0;
            mainDoor.GetComponent<Door_Script>().locked = true;
            mainDoor.GetComponent<Door_Script>().forcedLocked = true;

            if (!mainDoor.GetComponent<Door_Script>()._DoorAudioSource.isPlaying)
            {
                if (!played)
                {
                    mainDoor.GetComponent<Door_Script>()._DoorAudioSource.Play();
                }
                else if (played)
                {
                    this.gameObject.SetActive(false);
                }
            }
            else if (mainDoor.GetComponent<Door_Script>()._DoorAudioSource.isPlaying)
            {
                played = true;
            }
            
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.name == "Player")
        {
            collided = true;
            mainDoor.GetComponent<Door_Script>()._DoorAudioSource.clip = mainDoor.GetComponent<Door_Script>()._DoorSounds[0];
        }
    }
}
