using ScriptAPI;
using System;
using System.Collections.Specialized;
using System.Runtime.CompilerServices;
using System.Security.Cryptography;
using System.Threading.Tasks;
using System.Globalization; //for time??

using static Waypoint; //to get the waypoints you placed
using System.Reflection.PortableExecutable;
using System.Numerics;

public class GhostMovement : Script
{

    // [SerializeField]
    // float ManualMovementUnit = 3.0f;

    [SerializeField]
    float patrolSpeed = 0.1f;

    [SerializeField]
    int currTargetWaypt = 0;
    // float angle = 0f;

    [SerializeField]
    float deltaTime = 0f;

    [SerializeField]
    int NumOfWaypoints = 1;

    [SerializeField]
    bool isPatrol = true;
    [SerializeField]
    public bool isChasingPlayer = false;

    public GameObject player;

    public float speed;

    //public void ReadWaypoint(Waypoint wp)
    //{

    //}

    //// rotate the ghost to look at the target waypoint/player
    //void LookAtPoint(Vector3 targetPoint) //WIP (need to finish asap)
    //{
    //    Vector3 upVector = new Vector3(0f, 1f, 0f);
    //    Vector3 directionToTarget = targetPoint - gameObject.GetComponent<TransformComponent>().GetPosition();
    //    directionToTarget.Y = 0; //rotation is only around the y-axis

    //    //Quaternion targetRotation = Quaternion.LookRotation(directionToTarget, upVector);

    //    //gameObject.GetComponent<TransformComponent>().SetRotation(targetRotation);
    //    //set rotation to targetRotation;
    //}

    //static int CounterBehaviour(int current, int max)
    //{


    //    if (current > max)
    //    {
    //        current = 0; // Reset to 1 after reaching the maximum value
    //    }

    //    return current;
    //}

    public override void Awake()
    {
        walkingSounds = new string[11];
        walkingSounds[0] = "temp_step1";
        walkingSounds[1] = "temp_step1";
        walkingSounds[2] = "temp_step2";
        walkingSounds[3] = "temp_step3";
        walkingSounds[4] = "temp_step4";
        walkingSounds[5] = "temp_step5";
        walkingSounds[6] = "temp_step6";
        walkingSounds[7] = "temp_step7";
        walkingSounds[8] = "temp_step8";
        walkingSounds[9] = "temp_step9";
        walkingSounds[10] = "temp_step10";

        speed = 0.15f;
    }

    public override void Update()
    {
        //isChasingPlayer = !isPatrol;//can only be one or another
        //if (gameObject.GetComponent<SphereColliderComponent>().GetIsTrigger())
        //{
        //    isPatrol = false;
        //}
        //else
        //{
        //    isPatrol = true;
        //}
        ////Console.WriteLine(isChasingPlayer);

        //List<Vector3> waypointVector = new List<Vector3>();
        ////Console.WriteLine( GameObjectScriptFind("Waypoint"));
        ////Console.WriteLine($"Ghost sees target : ({GameObjectScriptFind("Waypoint").GetComponent<TransformComponent>().GetPosition().X}, {GameObjectScriptFind("Waypoint").GetComponent<TransformComponent>().GetPosition().Z})");
        ////Waypoint waypt1 = GameObjectScriptFind("Waypoint").GetComponent<TransformComponent>().GetPosition().Z;
        ////^ better way of accessing waypoint
        ////List<GameObject> test = MultipleGameObjectScriptFind("Waypoint");
        ////MultipleGameObjectScriptFind("Waypoint");
        //Vector3 pos = gameObject.GetComponent<TransformComponent>().GetPosition();
        ////Console.WriteLine(playerPos.X + " " + playerPos.Y + " " + playerPos.Z);
        ////Vector3 playerPos = player.GetComponent<TransformComponent>().GetPosition();
        //deltaTime += 0.01f; //i need help syncing with game time

        //for (int i = 0; i < NumOfWaypoints; ++i)
        //{
        //    //set position where the ghost will go (ghost approaches cabinet in the room)
        //    Vector3 wp1 = new Vector3(
        //        GameObjectScriptFind(i.ToString()).GetComponent<TransformComponent>().GetPosition().X,
        //        0,
        //        GameObjectScriptFind(i.ToString()).GetComponent<TransformComponent>().GetPosition().Z);
        //    //push back the waypoints
        //    waypointVector.Add(wp1);


        //}

        ////patrol in loop
        //if (isPatrol)
        //{

        //    //move the ghost if its posX and posZ is not = target Pos (target can be either player or the patrol waypoint)
        //    if (pos.X != waypointVector[currTargetWaypt].X)
        //    {
        //        if (Math.Abs(pos.X - waypointVector[currTargetWaypt].X) <= patrolSpeed) { pos.X = waypointVector[currTargetWaypt].X; } //stop moving
        //        if (pos.X > waypointVector[currTargetWaypt].X) { pos.X -= patrolSpeed; }
        //        else if (pos.X < waypointVector[currTargetWaypt].X) { pos.X += patrolSpeed; }

        //    }
        //    if (pos.Z != waypointVector[currTargetWaypt].Z)
        //    {

        //        if (Math.Abs(pos.Z - waypointVector[currTargetWaypt].Z) <= patrolSpeed) { pos.Z = waypointVector[currTargetWaypt].Z; } //stop
        //        if (pos.Z > waypointVector[currTargetWaypt].Z) { pos.Z -= patrolSpeed; }
        //        else if (pos.Z < waypointVector[currTargetWaypt].Z) { pos.Z += patrolSpeed; }

        //    }
        //    if (pos.X == waypointVector[currTargetWaypt].X && pos.Z == waypointVector[currTargetWaypt].Z)
        //    {
        //        currTargetWaypt++; //move to next waypoint
        //        if (currTargetWaypt == NumOfWaypoints) { currTargetWaypt = 0; }

        //    }
        //}
        //else
        //{
        //    //Vector3 diff = (playerPos - pos).normalise();
        //    //Vector3 updatePos = diff * patrolSpeed;
        //    //pos.X = updatePos.X;
        //    //pos.Z = updatePos.Z;
        //}

        //// pos.X = startingX + patrolRadius * (float)Math.Cos(angle);
        //// pos.Z = startingZ + patrolRadius * (float)Math.Sin(angle);

        //gameObject.GetComponent<TransformComponent>().SetPositionX(pos.X);

        //gameObject.GetComponent<TransformComponent>().SetPositionZ(pos.Z);

        ////Console.WriteLine($"Enemy Position: ({pos.X}, {pos.Z})");
        ////Console.WriteLine($"Going to waypoint at : ({wp1.X}, {wp1.Z})");

        // Play monster walking sound
        if (playSound)
        {
            playSound = PlayMonsterWalkingSound();
        }
        else if (isChasingPlayer) // done playing sound, chasing player
        {
            ScriptAPI.Vector3 originalPosition = transform.GetPosition();
            ScriptAPI.Vector2 nextPosition = WaypointPathfinder.NextStep(new ScriptAPI.Vector2(originalPosition.X, originalPosition.Z), speed);
            transform.SetPosition(new ScriptAPI.Vector3(nextPosition.X, originalPosition.Y, nextPosition.Y));
            //Console.WriteLine(nextPosition.X + "\t\t" + nextPosition.Y);
        }
    }

    public int walkingSoundCounter = -1;
    public String[] walkingSounds;
    public bool playSound;
    public float playSoundTimer;

    public bool PlayMonsterWalkingSound()
    {
        AudioComponent audio = gameObject.GetComponent<AudioComponent>();

        if (audio.finished(walkingSounds[walkingSoundCounter]))
        {
            if (playSoundTimer < 0)
            {
                audio.stop(walkingSounds[walkingSoundCounter]);
                ++walkingSoundCounter;

                if (walkingSoundCounter == 10)  // finished
                    return false;

                audio.play(walkingSounds[walkingSoundCounter]);
                playSoundTimer = 1.0f / walkingSoundCounter;
            }
            else
            {
                playSoundTimer -= Time.deltaTime;
            }
        }

        return true;
    }

    public void AlertMonster(int doorIndex)
    {
        speed += 0.1f;
        playSoundTimer = 1.0f;
        walkingSoundCounter = 0;
        isPatrol = false;
        isChasingPlayer = true;

        transform.SetPositionX(-2840.0f);
        transform.SetPositionZ(-650.0f);
        // Teleport monster based on door
        WaypointPathfinder.FindPath(new ScriptAPI.Vector2(-2840, -650), new ScriptAPI.Vector2(player.transform.GetPosition().X, player.transform.GetPosition().Z)); // temp position

        player.transform.SetPosition(transform.GetPosition());

        playSound = true;
    }
}
