/*!*************************************************************************
****
\file GhostMovement.cs
\author Thea Sea
\par DP email: thea.sea@digipen.edu
\par Course: csd3450
\date 15-1-2024
\brief  Script for ghost movement
****************************************************************************
***/
using ScriptAPI;
using System.Security.Cryptography;

public class GhostMovement : Script
{
    public float speed;

    String[] monsterPatrol;
    String[] monsterAlert;

    public GameBlackboard gameBlackboard;

    #region Monster Sounds

    public float soundSpeed;
    public int walkingSoundCounter = -1;
    public float playSoundTimer;

    public String[] walkingSounds;
    public String voiceClips;

    #endregion

    #region Chasing Player Variables

    public bool isChasingPlayer = false;
    public bool playerMoved;
    public GameObject player;

    #endregion

    #region Moving To Door Variables

    private Vector2 doorPosition;

    #endregion

    #region General Event Variables

    // For initializing events 
    public bool startEvent;

    #endregion

    #region Bedroom Hiding Event Variables

    public GameObject bedroomHidingGameObject; // (Bedroom) Hide Closet > Door_2 > Door_2
    public int eventStep;
    public bool bedroomHideEventDone;
    public GameObject SHDoor; // Small Hallway Door

    #endregion

    #region Living Dining Room Event Variables

    public float livingDiningRoomStandingTimer;
    public bool livingDiningRoomEventDone;

    #endregion

    #region Living Room Hiding Event

    public float livingRoomHidingTimer;
    public bool livingRoomHideEventDone;

    #endregion

    #region Gallery 

    public GameObject galleryHidingGameObject; // (Study) Hide Closet > Door_2 > Door_2
    public bool galleryHideEventDone;
    public bool galleryChaseEventDone;

    #endregion

    public enum GhostEvent
    {
        Nothing,
        PlayingWalkingSound,
        ChasingPlayer,
        MovingToDoor,
        BedroomHidingEvent,
        LivingDiningRoomEvent,
        LivingRoomHidingEvent,
        GalleryHidingEvent,
        GalleryChasingEvent
    }

    [DontSerializeField]
    [HideInInspector]
    public GhostEvent currentEvent;
    [DontSerializeField]
    [HideInInspector]
    public GhostEvent previousEvent;

    public override void Awake()
    {
        walkingSounds = new string[8];
        walkingSounds[0] = "mon_woodstep1";
        walkingSounds[1] = "mon_woodstep2";
        walkingSounds[2] = "mon_woodstep3";
        walkingSounds[3] = "mon_woodstep4";
        walkingSounds[4] = "mon_woodstep5";
        walkingSounds[5] = "mon_woodstep6";
        walkingSounds[6] = "mon_woodstep7";
        walkingSounds[7] = "mon_woodstep8";

        monsterPatrol = new string[8];
        monsterPatrol[0] = "mon_patrol1";
        monsterPatrol[1] = "mon_patrol2";
        monsterPatrol[2] = "mon_patrol3";
        monsterPatrol[3] = "mon_patrol4";
        monsterPatrol[4] = "mon_patrol5";
        monsterPatrol[5] = "mon_patrol6";
        monsterPatrol[6] = "mon_patrol7";
        monsterPatrol[7] = "mon_patrol8";

        monsterAlert = new string[7];
        monsterAlert[0] = "mon_alerted1";
        monsterAlert[1] = "mon_alerted2";
        monsterAlert[2] = "mon_alerted3";
        monsterAlert[3] = "mon_alerted4";
        monsterAlert[4] = "mon_alerted5";
        monsterAlert[5] = "mon_alerted6";
        monsterAlert[6] = "mon_alerted7";

        voiceClips = "pc_monstergoesaway1";

        speed = 3.0f;
        soundSpeed = 1.0f;
        eventStep = 0;

        playerMoved = false;
        bedroomHideEventDone = false;
        livingDiningRoomEventDone = false;
        livingRoomHideEventDone = false;
        galleryHideEventDone = false;
        startEvent = false;

        currentEvent = GhostEvent.Nothing;

        transform.SetPositionX(-2840.0f);
        transform.SetPositionZ(-650.0f);
    }
    public override void Update()
    {
        if (gameBlackboard.gameState == GameBlackboard.GameState.Paused)
        {
            return;
        }

        // Testing (to be removed)
        if (Input.GetKeyDown(Keycode.K))
        {
            currentEvent = GhostEvent.LivingDiningRoomEvent;
            startEvent = true;

            // Teleporting monster to Living Room - Dining Room door for next event
            transform.SetPositionX(319.0f);
            transform.SetPositionZ(-379.0f);
        }
        // Testing (to be removed)
        if (Input.GetKeyDown(Keycode.L))
        {
            currentEvent = GhostEvent.LivingRoomHidingEvent;
            startEvent = true;
        }
        // Testing (to be removed)
        if (Input.GetKeyDown(Keycode.M))
        {
            // Teleporting monster to Main Entrance
            transform.SetPositionX(-272.0f);
            transform.SetPositionZ(192.0f);
        }

        Vector2 ghostPosition = new Vector2(transform.GetPosition().X, transform.GetPosition().Z);
        Vector2 playerPosition = new Vector2(player.transform.GetPosition().X, player.transform.GetPosition().Z);

        switch (currentEvent)
        {
            case GhostEvent.Nothing:

                if (WaypointPathfinder.SameRoom(ghostPosition, playerPosition)) // If player is in the same room as ghost = sees player, chase player
                {
                    // NOTE: May want to add in "not hiding" condition
                    currentEvent = GhostEvent.ChasingPlayer;
                }

                break;

            case GhostEvent.PlayingWalkingSound:

                if (!PlayMonsterWalkingSound())
                {
                    currentEvent = GhostEvent.MovingToDoor; // done playing sound, move to door that player failed the lockpick
                }

                break;

            case GhostEvent.ChasingPlayer:
                Console.WriteLine("ChasingPlayer");
                if (!WaypointPathfinder.SameRoom(ghostPosition, playerPosition)) // If player moves out of the room, ghost doesnt chase (MAYBE CHANGE)
                {
                    currentEvent = GhostEvent.Nothing;
                    break;
                }

                // If touches, loses
                if (Vector2.Distance(ghostPosition, playerPosition) <= 40.0f)
                {
                    // Jumpscare scene
                    gameBlackboard.gameState = GameBlackboard.GameState.Jumpscare; // Locks everything else, play jumpscare

                    SetEnabled(false);
                    player.GetComponent<FPS_Controller_Script>().SetEnabled(false);
                    gameObject.GetComponent<JumpscareScript>().SetEnabled(true);
                    return;
                }
                else
                {
                    // Go straight to player
                    //Vector3 originalPosition = transform.GetPosition();
                    //Vector2 nextPosition = Vector2.MoveTowards(ghostPosition, playerPosition, speed);
                    //transform.SetPosition(new Vector3(nextPosition.X, originalPosition.Y, nextPosition.Y));

                    MoveTo(playerPosition, speed);
                }
                playerMoved = true;
                speed += 0.001f;

                break;

            case GhostEvent.MovingToDoor:
                Console.WriteLine("MovingToDoor");

                if (WaypointPathfinder.SameRoom(ghostPosition, playerPosition)) // If player is in the same room as ghost, chase player
                {
                    currentEvent = GhostEvent.ChasingPlayer;
                }
                else // Move to doors
                {
                    if (playerMoved)
                    {
                        WaypointPathfinder.FindPath(ghostPosition, playerPosition);
                    }
                    Vector3 originalPosition = transform.GetPosition();
                    Vector2 nextPosition = WaypointPathfinder.NextStep(new Vector2(originalPosition.X, originalPosition.Z), speed);
                    transform.SetPosition(new Vector3(nextPosition.X, originalPosition.Y, nextPosition.Y));
                    playerMoved = false;

                    if (doorPosition.X == transform.GetPosition().X && doorPosition.Y == transform.GetPosition().Z) // Reached
                    {
                        currentEvent = GhostEvent.Nothing;
                    }
                }
                AudioComponent audio = gameObject.GetComponent<AudioComponent>();
                int ran_num = RandomNumberGenerator.GetInt32(7);
                audio.play(monsterAlert[ran_num]);
                audio.set3DCoords(transform.GetPosition(), monsterAlert[ran_num]);

                break;

            case GhostEvent.BedroomHidingEvent:

                BedroomHidingEvent();

                break;

            case GhostEvent.LivingDiningRoomEvent: // 1. LivingDiningRoomEvent => move from dining room - living room door to dining room - main hall door & disappear

                LivingDiningRoomEvent();

                break;

            case GhostEvent.LivingRoomHidingEvent: // 2. LivingRoomHidingEvent => move from living room - right wing door to left of couch, look around, walk into dining room painting & stay there

                LivingRoomHidingEvent();

                break;

            case GhostEvent.GalleryHidingEvent:

                GalleryHidingEvent();

                break;

            case GhostEvent.GalleryChasingEvent:

                GalleryChasingEvent();

                break;
        }
    }

    public void PlayMonsterWalkingSoundInitial()
    {
        AudioComponent audio = gameObject.GetComponent<AudioComponent>();
        walkingSoundCounter = 0;
        audio.play(walkingSounds[walkingSoundCounter]);
        Vector3 temp = new Vector3(1000, 1000, 0);
        audio.set3DCoords(temp/*transform.GetPosition()*/ , walkingSounds[walkingSoundCounter]);
        currentEvent = GhostEvent.PlayingWalkingSound;
    }
    public bool PlayMonsterWalkingSound()
    {
        AudioComponent audio = gameObject.GetComponent<AudioComponent>();
        Vector3 temp = new Vector3(1000, 1000, 0);

        if (audio.finished(walkingSounds[walkingSoundCounter]))
        {
            if (playSoundTimer < 0)
            {
                audio.stop(walkingSounds[walkingSoundCounter]);
                ++walkingSoundCounter;

                if (walkingSoundCounter == 7)  // finished
                {
                    audio.play("pc_afterscare_heartbeat");
                    return false;
                }

                audio.play(walkingSounds[walkingSoundCounter]);
                audio.set3DCoords(temp/*transform.GetPosition()*/, walkingSounds[walkingSoundCounter]);
                playSoundTimer = soundSpeed - walkingSoundCounter * 0.05f;

                //audio.set3DCoords(transform.GetPosition());
                //if (!triggerBedroomHideEvent)
                //{
                //    int ra = RandomNumberGenerator.GetInt32(8);
                //    audio.play(monsterPatrol[ra]);
                //    audio.set3DCoords(temp /*transform.GetPosition()*/, monsterPatrol[ra]);
                //}
            }
            else
            {
                playSoundTimer -= Time.deltaTime;
            }
        }

        return true;
    }

    public void AlertMonster()
    {
        soundSpeed -= 0.1f;
        speed += 0.2f;
        playSoundTimer = soundSpeed;
        isChasingPlayer = true;

        // Move monster to player position if lockpick fails
        doorPosition = new Vector2(player.transform.GetPosition().X, player.transform.GetPosition().Z);
        WaypointPathfinder.FindPath(new Vector2(-2840, -650), doorPosition); // NOTE: temp position

        player.transform.SetPosition(transform.GetPosition());

        PlayMonsterWalkingSoundInitial();
    }


    public bool MoveTo(Vector2 destination, float speed)
    {
        Vector2 ghostPosition = new Vector2(transform.GetPosition().X, transform.GetPosition().Z);
        Vector2 nextPosition = Vector2.MoveTowards(ghostPosition, destination, speed);
        transform.SetPosition(new Vector3(nextPosition.X, transform.GetPosition().Y, nextPosition.Y));

        #region Turning monster to face where its walking

        Vector2 lineToNextPosition = new Vector2(nextPosition.X - ghostPosition.X, nextPosition.Y - ghostPosition.Y);
        float lineToNextPositionLength = Mathf.Sqrt(lineToNextPosition.X * lineToNextPosition.X + lineToNextPosition.Y * lineToNextPosition.Y);
        float forwardVectorLength = Mathf.Sqrt(Vector3.Forward().X * Vector3.Forward().X + Vector3.Forward().Z * Vector3.Forward().Z);

        float rotationOfMonster = Mathf.Acos((lineToNextPosition.X * Vector3.Forward().X + lineToNextPosition.Y * Vector3.Forward().Z) / (lineToNextPositionLength * forwardVectorLength));

        if (lineToNextPosition.X < 0)
            transform.SetRotation(new Vector3(0.0f, -rotationOfMonster, 0.0f));
        else
            transform.SetRotation(new Vector3(0.0f, rotationOfMonster, 0.0f));

        #endregion

        if (transform.GetPosition().X == destination.X && transform.GetPosition().Z == destination.Y)
        {
            return true;
        }

        return false;
    }

    public void BedroomHidingEvent()
    {
        Console.WriteLine("BedroomHidingEvent");

        if (startEvent) // Initialize variables (teleporting monster to starting position etc)
        {
            transform.SetPosition(new Vector3(1790.0f, transform.GetPosition().Y, -750.0f));
            eventStep = 0;
            startEvent = false;
            //Console.WriteLine("initialized bedroom hiding event");
        }

        if (!bedroomHidingGameObject.GetComponent<Hiding>().hiding) // If player comes out of hiding, monster will chase player
        {
            isChasingPlayer = true;
        }
        else // If player goes back into closet / does not come out, monster will just move and disappear
        {
            isChasingPlayer = false;
        }

        Vector3 originalPosition = transform.GetPosition();
        Vector2 ghostPosition = new Vector2(originalPosition.X, originalPosition.Z);
        AudioComponent audio = gameObject.GetComponent<AudioComponent>();

        switch (eventStep)
        {
            case 0: // Moving from SH door to end of bedframe in bed

                if (MoveTo(new Vector2(1790, -323), 5.0f))
                {
                    ++eventStep;
                }

                audio.play("pc_afterscare_breathing");
                audio.play("pc_afterscare_heartbeat");
                break;

            case 1: // Moving to player / hiding closet

                if (MoveTo(new Vector2(2167, -100), 5.0f))
                {
                    ++eventStep;
                }

                break;

            case 2: // Event done

                bedroomHideEventDone = true;
                currentEvent = GhostEvent.Nothing;
                isChasingPlayer = false;
                SHDoor.GetComponent<Door_Script>().forcedLocked = false;

                // Teleporting monster to Living Room - Dining Room door for next event
                transform.SetPositionX(319.0f);
                transform.SetPositionZ(-379.0f);
                transform.SetRotationY(-(float)(0.5 * Math.PI));

                audio.FadeOut(2, "pc_afterscare_breathing");
                audio.FadeOut(2, "pc_afterscare_heartbeat");
                audio.play(voiceClips);
                GameplaySubtitles.counter = 11; // wth was that

                break;
        }

    }

    public void LivingDiningRoomEvent()
    {
        Console.WriteLine("LivingDiningRoomEvent");

        if (startEvent) // Initialize variables
        {
            livingDiningRoomStandingTimer = 1.0f;
            eventStep = 0;
            startEvent = false;
            //Console.WriteLine("initialized living dining room event");
        }

        Vector2 ghostPosition = new Vector2(transform.GetPosition().X, transform.GetPosition().Z);
        Vector2 nextPosition = new Vector2(0.0f, 0.0f);

        switch (eventStep)
        {
            case 0: // Stay for a while

                if (livingDiningRoomStandingTimer <= 0)
                {
                    ++eventStep;
                }
                livingDiningRoomStandingTimer -= Time.deltaTime;

                break;

            case 1: // Move to beside dining room - main entrance door (making it look a little better)

                if (MoveTo(new Vector2(-272, -200), 5.0f))
                {
                    ++eventStep;
                }

                break;

            case 2: // Move to dining room - main entrance door & disappear

                if (MoveTo(new Vector2(-272, -80), 5.0f))
                {
                    ++eventStep;
                }

                break;

            case 3: // Event done

                livingDiningRoomEventDone = true;
                currentEvent = GhostEvent.Nothing;

                // Teleporting monster away so player wont see it (for now the position is in the gallery)
                transform.SetPositionX(-1920.0f);
                transform.SetPositionZ(175.0f);

                break;
        }
    }

    // LivingRoomHidingEvent => move from living room - right wing door to left of couch, look ard, walk into dining room painting & stay there
    public void LivingRoomHidingEvent()
    {
        Console.WriteLine("LivingRoomHidingEvent");

        if (startEvent) // Initialize variables
        {
            livingRoomHidingTimer = 1.0f;
            eventStep = 0;
            startEvent = false;

            // Teleporting monster to behind the living room - right hall door
            transform.SetPositionX(938.0f);
            transform.SetPositionZ(17.0f);

            //Console.WriteLine("initialized living room hiding event");
        }

        switch (eventStep)
        {
            case 0: // Move to couch

                if (MoveTo(new Vector2(938.0f, -379.0f), 5.0f))
                {
                    ++eventStep;
                }

                break;

            case 1: // Look around / wait

                if (livingRoomHidingTimer <= 0)
                {
                    ++eventStep;
                }
                livingRoomHidingTimer -= Time.deltaTime;

                break;

            case 2: // Move to living room - dining room door

                if (MoveTo(new Vector2(156.0f, -379.0f), 5.0f))
                {
                    ++eventStep;
                }

                break;

            case 3: // Move to picture in dining room

                if (MoveTo(new Vector2(-58.0f, -1060.0f), 5.0f))
                {
                    ++eventStep;
                }

                break;

            case 4: // Event done

                livingRoomHideEventDone = true;
                currentEvent = GhostEvent.Nothing;

                break;
        }
    }

    public void GalleryHidingEvent()
    {
        Console.WriteLine("GalleryHidingEvent");
        if (startEvent) // Initialize variables (teleporting monster to starting position etc)
        {
            transform.SetPosition(new Vector3(-1920.0f, transform.GetPosition().Y, -300.0f));
            eventStep = 0;
            startEvent = false;
        }

        if (!galleryHidingGameObject.GetComponent<GalleryHiding>().hiding) // If player comes out of hiding, monster will chase player
        {
            isChasingPlayer = true;
        }
        else // If player goes back into closet / does not come out, monster will just move and disappear
        {
            isChasingPlayer = false;
        }

        AudioComponent audio = gameObject.GetComponent<AudioComponent>();

        switch (eventStep)
        {
            case 0: // Walk to Study Room Door

                if (MoveTo(new Vector2(-2850, -300), 10.0f))
                {
                    ++eventStep;
                }

                audio.play("pc_afterscare_breathing");
                audio.play("pc_afterscare_heartbeat");
                break;

            case 1: // Walk into Study Room

                if (MoveTo(new Vector2(-2850, 175), 5.0f))
                {
                    ++eventStep;
                }

                break;

            case 2: // Walk out of Study Room

                if (MoveTo(new Vector2(-1920, 175), 5.0f))
                {
                    ++eventStep;
                }

                break;

            case 3: // Event done

                galleryHideEventDone = true;
                currentEvent = GhostEvent.Nothing;
                isChasingPlayer = false;
                GalleryHiding.GhostShouldMove = false;

                audio.FadeOut(2, "pc_afterscare_breathing");
                audio.FadeOut(2, "pc_afterscare_heartbeat");

                break;
        }
    }

    public void GalleryChasingEvent() 
    {
        Console.WriteLine("GalleryChasingEvent");
        if (startEvent) // Initialize variables (teleporting monster to starting position etc)
        {
            transform.SetPosition(new Vector3(-1920.0f, transform.GetPosition().Y, -300.0f));
            eventStep = 0;
            startEvent = false;
        }

        if (!galleryHidingGameObject.GetComponent<GalleryHiding>().hiding) // If player comes out of hiding, monster will chase player
        {
            isChasingPlayer = true;
        }
        else // If player goes back into closet / does not come out, monster will just move and disappear
        {
            isChasingPlayer = false;
        }

        switch (eventStep)
        {
            case 0: // Walk to Study Room Door

                if (MoveTo(new Vector2(-1414, -729), 5.0f))
                {
                    ++eventStep;
                }

                break;

            case 1: // Event done

                galleryChaseEventDone = true;
                currentEvent = GhostEvent.Nothing;
                isChasingPlayer = false;

                break;
        }
    }
}