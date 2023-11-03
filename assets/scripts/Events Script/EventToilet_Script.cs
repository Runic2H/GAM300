using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EventToilet_Script : MonoBehaviour
{
    bool collided;
    bool playedAudio;
    int audioCount = -1;

    public bool completedEvent;
    public AudioSource myAS;
    public AudioClip[] showeringSFX;

    // Update is called once per frame
    void Update()
    {
        if (collided && !completedEvent)
        {
            if (!myAS.isPlaying)
            {
                if (!playedAudio)
                {
                    myAS.clip = showeringSFX[audioCount += 1];
                    myAS.Play();
                    playedAudio = true;

                    if (audioCount == 1)
                    {
                        myAS.loop = true;
                    }
                    else
                    {
                        myAS.loop = false;
                    }
                }
            }
            else
            {
                playedAudio = false;
            }
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "MainCamera")
        {
            collided = true;
        }
    }
}
