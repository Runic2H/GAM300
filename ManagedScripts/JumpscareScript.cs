/*!*************************************************************************
****
\file JumpscareScript.cs
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\par Course: csd3450
\date 9-2-2024
\brief  Script to toggle map
****************************************************************************
***/
using ScriptAPI;

public class JumpscareScript : Script
{
    public GameObject player;
    public int jumpscareSequenceIndex;

    private float yRotation = 0.0f;
    private bool fadeOut = true;
    private float incrementFading = Time.deltaTime / 2f;
    private float alpha = 0;

    private Vector3 originalPosition;
    private float screamTimer = 0;
    public GameObject playerCamera;

    public override void Awake()
    {
        jumpscareSequenceIndex = 1;
        alpha = 0;
        GraphicsManagerWrapper.SetFadeFactor(0.2f);
        //jumpscareSequenceIndex = 0;
        //SetEnabled(false);
        originalPosition = transform.GetPosition();
        screamTimer = 2.5f;
        playerCamera.transform.SetPosition(new Vector3(0.0f , 90.0f, 0.0f));
        player.transform.SetPosition(new Vector3(0.0f , 90.0f, 0.0f));
    }
    public override void Update()
    {
        //if (fadeOut == true)
        //{
        //    alpha += incrementFading;
        //    alpha = Mathf.Clamp(alpha, 0, 0.2f);
        //      GraphicsManagerWrapper.SetFadeFactor(0.2f);
        //    if (alpha >= 0.2f)
        //    {
        //        fadeOut = false;
        //    }
        //}

        switch (jumpscareSequenceIndex)
        {
            // 1. calculating rotations
            case 0:

                GraphicsManagerWrapper.ToggleViewFrom2D(false);

                // Turning towards ghost
                Vector2 lineToNextPosition = new Vector2(transform.GetPosition().X - player.transform.GetPosition().X, transform.GetPosition().Z - player.transform.GetPosition().Z);
                float lineToNextPositionLength = Mathf.Sqrt(lineToNextPosition.X * lineToNextPosition.X + lineToNextPosition.Y * lineToNextPosition.Y);
                float forwardVectorLength = Mathf.Sqrt(Vector3.Forward().X * Vector3.Forward().X + Vector3.Forward().Z * Vector3.Forward().Z);

                yRotation = Mathf.Acos((lineToNextPosition.X * Vector3.Forward().X + lineToNextPosition.Y * Vector3.Forward().Z) / (lineToNextPositionLength * forwardVectorLength));

                if (lineToNextPosition.X >= 0)
                    yRotation = 360 - (float)(yRotation / Math.PI * 180.0f);
                else
                    yRotation = (float)(yRotation / Math.PI * 180.0f);

                ++jumpscareSequenceIndex;

                break;

            // 2. turn player camera towards ghost, then up fast
            case 1:

                //player.transform.SetRotationY(Mathf.LerpAngle(player.transform.GetRotation().Y, yRotation, Time.deltaTime * 12));
                //player.GetComponent<FPS_Controller_Script>().playerCamera.transform.SetRotationX(
                //    Mathf.LerpAngle(player.GetComponent<FPS_Controller_Script>().playerCamera.transform.GetRotation().X, 28, Time.deltaTime * 12));

                //Console.WriteLine(yRotation);

                //if (player.transform.GetRotation().Y >= 360)
                //{
                //    player.transform.SetRotationY(player.transform.GetRotation().Y - 360);
                //}

                //if (player.transform.GetRotation().Y >= yRotation - 3 && player.transform.GetRotation().Y <= yRotation + 3)
                //{
                //    gameObject.GetComponent<AudioComponent>().stopAll();
                //    gameObject.GetComponent<AudioComponent>().play("mon_death");
                //    ++jumpscareSequenceIndex;
                //}

                GraphicsManagerWrapper.ToggleViewFrom2D(false);
                gameObject.GetComponent<AudioComponent>().play("mon_death");
                ++jumpscareSequenceIndex;
                break;

            // 3. (may want to add scream sounds here before next step)
            // Add head shaking
            case 2:

                transform.SetPosition(originalPosition + new Vector3(ScriptAPI.Random.Range(-2.0f, 2.0f), ScriptAPI.Random.Range(-2.0f, 2.0f), 0.0f));

                if (screamTimer <= 0.0f)
                {
                    gameObject.GetComponent<AudioComponent>().stop("mon_death");
                    transform.SetPosition(originalPosition);
                    ++jumpscareSequenceIndex;
                }
                screamTimer -= Time.deltaTime;

                break;

            // 4. move ghost head down to player head (estimate) 
            case 3:

                Vector2 ghostPosition = new Vector2(transform.GetPosition().X, transform.GetPosition().Z);
                Vector2 playerPositon = new Vector2(player.transform.GetPosition().X, player.transform.GetPosition().Z);
                Vector2 nextPosition = Vector2.MoveTowards(ghostPosition, playerPositon, 10);
                transform.SetPosition(new Vector3(nextPosition.X, transform.GetPosition().Y - 4.5f, nextPosition.Y));

                if (transform.GetPosition().X == playerPositon.X && transform.GetPosition().Z == playerPositon.Y)
                {
                    ++jumpscareSequenceIndex;
                }

                break;

            // 5. lost screen
            case 4:
                Input.HideMouse(false);
                Input.Lock(false);
                SceneLoader.LoadEndGameCredits();
                break;
        }
    }
}
