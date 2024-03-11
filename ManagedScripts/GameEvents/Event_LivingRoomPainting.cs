using ScriptAPI;
using System;

public class EventLivingRoomPainting : Script
{
    public GameObject? painting;
    public bool Dialogue = false;
    public bool DialogueDone = false;
    public float TestTimer = 3.0f;

    public float position = 0.0f;

    public override void Update()
    {
        if (gameObject.GetComponent<RigidBodyComponent>().IsRayHit() && gameObject.GetComponent<RigidBodyComponent>().IsPlayerCast() && Input.GetKeyDown(Keycode.E))
        {
            Dialogue = true;
        }

        if (Dialogue && !DialogueDone)
        {
            //Insert Marvin Dialogue here
            TestTimer -= Time.deltaTime;
        }

        if (TestTimer <= 0.0f)
        {
            DialogueDone = true;
            TestTimer = 2.0f;
        }

        if (DialogueDone)
        {
            position = Mathf.Lerp(gameObject.transform.GetPosition().Y, 0.0f, 2.0f * Time.deltaTime);
            gameObject.transform.SetPositionY(position);
            TestTimer -= Time.deltaTime;
            if (TestTimer <= 0.0f)
            {
                gameObject.SetActive(false);
            }
        }
    }

}