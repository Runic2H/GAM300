using ScriptAPI;
using System;

public class WaypointSetup : Script
{
    float monsterPositionX;
    float monsterPositionY;

    // Rooms
    public int MainEntrance_Room;
    public int Toilet_Room;
    public int SH_Room;
    public int Bed_Room;
    public int Living_Room;
    public int RightWing_Room;
    public int Dining_Room;
    public int Kitchen_Room;
    public int Gallery_Room;
    public int Study_Room;
    public int LeftWing_Room;

    // Waypoints
    public int GalleryFirst_Waypoint;
    public int GallerySecond_Waypoint;
    public int GalleryStudy_DoorWaypoint;

    public int Study_Waypoint;
    public int StudyLeftWing_DoorWaypoint;

    public int LeftWing_Waypoint;
    public int GalleryLeftWing_DoorWaypoint;
    public int LeftWingMainEntrance_DoorWaypoint;
    public int DiningMainEntrance_DoorWaypoint;
    public int RightWingMainEntrance_DoorWaypoint;

    public int MainEntrance_Waypoint;
    public int RightWingFirst_Waypoint;
    public int RightWingSecond_Waypoint;
    public int RightWingThird_Waypoint;
    public int RightWingLiving_DoorWaypoint;

    public int RightWingBed_DoorWaypoint;

    public int BedFirst_Waypoint;
    public int BedSecond_Waypoint;
    public int BedSH_DoorWaypoint;

    public int SHFirst_Waypoint;
    public int SHSecond_Waypoint;
    public int SHLiving_DoorWaypoint;

    public int SHToilet_DoorWaypoint;
    public int Toilet_Waypoint;

    public int Living_Waypoint;
    public int LivingDining_DoorWaypoint;
    public int Dining_Waypoint;

    public int DiningKitchen_DoorWaypoint;
    public int Kitchen_Waypoint;

    public int RightWingStairs_DoorWaypoint;

    public bool playerMoved;
    public float timer;

    public override void Awake()
    {
        WaypointPathfinder.ClearRoomWaypoints();

        // Rooms
        MainEntrance_Room = WaypointPathfinder.AddRoom(new Vector2(-762.0f, -185.0f), new Vector2(198.0f, 952.0f));

        Toilet_Room = WaypointPathfinder.AddRoom(new Vector2(2002.0f, -1351.0f), new Vector2(2635.0f, -728.0f));
        SH_Room = WaypointPathfinder.AddRoom(new Vector2(1575.0f, -1351.0f), new Vector2(2002.0f, -728.0f));
        Bed_Room = WaypointPathfinder.AddRoom(new Vector2(1575.0f, -728.0f), new Vector2(2635.0f, 81.0f));
        Living_Room = WaypointPathfinder.AddRoom(new Vector2(350.0f, -1351.0f), new Vector2(1575.0f, -14.0f));
        RightWing_Room = WaypointPathfinder.AddRoom(new Vector2(198.0f, -14.0f), new Vector2(2635.0f, 607.0f));

        Dining_Room = WaypointPathfinder.AddRoom(new Vector2(-870.0f, -1351.0f), new Vector2(350.0f, -185.0f));
        Kitchen_Room = WaypointPathfinder.AddRoom(new Vector2(-1328.0f, -1351.0f), new Vector2(-870.0f, -48.0f));
        Gallery_Room = WaypointPathfinder.AddRoom(new Vector2(-3415.0f, -1351.0f), new Vector2(-1328.0f, -48.0f));
        Study_Room = WaypointPathfinder.AddRoom(new Vector2(-3415.0f, -48.0f), new Vector2(-2366.0f, 708.0f));
        LeftWing_Room = WaypointPathfinder.AddRoom(new Vector2(-2327.0f, -48.0f), new Vector2(-762.0f, 442.0f));

        // Waypoints
        GalleryFirst_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(-2840.0f, -650.0f));
        GallerySecond_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(-1929.0f, -650.0f));
        GalleryStudy_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(-2840.0f, -70.0f));

        Study_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(-2840.0f, 178.0f));
        StudyLeftWing_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(-2352.0f, 178.0f));

        LeftWing_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(-1929.0f, 178.0f));
        GalleryLeftWing_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(-1929.0f, -70.0f));

        LeftWingMainEntrance_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(-756.0f, 226.0f));
        DiningMainEntrance_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(-272.0f, -124.0f));
        RightWingMainEntrance_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(211.0f, 177.0f));

        MainEntrance_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(-272.0f, 192.0f));
        RightWingFirst_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(938.0f, 177.0f));
        RightWingSecond_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(1408.0f, 366.0f));
        RightWingThird_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(1790.0f, 366.0f));
        RightWingLiving_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(938.0f, -3.0f));

        RightWingBed_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(1790.0f, 113.0f));

        BedFirst_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(1790.0f, -323.0f));
        BedSecond_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(2167.0f, -100.0f));
        BedSH_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(1790.0f, -740.0f));

        SHFirst_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(1790.0f, -984.0f));
        SHSecond_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(1790.0f, -1117.0f));
        SHLiving_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(1547.0f, -984.0f));

        SHToilet_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(2022.0f, -1117.0f));
        Toilet_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(2320.0f, -1117.0f));

        Living_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(938.0f, -379.0f));
        LivingDining_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(319.0f, -379.0f));
        Dining_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(-268.0f, -561.0f));

        DiningKitchen_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(-872.0f, -712.0f));
        Kitchen_Waypoint = WaypointPathfinder.AddWaypoint(new Vector2(-1074.0f, -712.0f));

        RightWingStairs_DoorWaypoint = WaypointPathfinder.AddWaypoint(new Vector2(2633.0f, 366.0f));

        // Adding connections
        WaypointPathfinder.AddWaypointRoomConnection(GalleryFirst_Waypoint, Gallery_Room);
        WaypointPathfinder.AddWaypointRoomConnection(GallerySecond_Waypoint, Gallery_Room);

        WaypointPathfinder.AddWaypointRoomConnection(GalleryStudy_DoorWaypoint, Gallery_Room);
        WaypointPathfinder.AddWaypointRoomConnection(GalleryStudy_DoorWaypoint, Study_Room);
        WaypointPathfinder.AddWaypointRoomConnection(Study_Waypoint, Study_Room);

        WaypointPathfinder.AddWaypointRoomConnection(StudyLeftWing_DoorWaypoint, Study_Room);
        WaypointPathfinder.AddWaypointRoomConnection(StudyLeftWing_DoorWaypoint, LeftWing_Room);
        WaypointPathfinder.AddWaypointRoomConnection(LeftWing_Waypoint, LeftWing_Room);

        WaypointPathfinder.AddWaypointRoomConnection(GalleryLeftWing_DoorWaypoint, Gallery_Room);
        WaypointPathfinder.AddWaypointRoomConnection(GalleryLeftWing_DoorWaypoint, LeftWing_Room);

        WaypointPathfinder.AddWaypointRoomConnection(LeftWingMainEntrance_DoorWaypoint, LeftWing_Room);
        WaypointPathfinder.AddWaypointRoomConnection(LeftWingMainEntrance_DoorWaypoint, MainEntrance_Room);
        WaypointPathfinder.AddWaypointRoomConnection(DiningMainEntrance_DoorWaypoint, Dining_Room);
        WaypointPathfinder.AddWaypointRoomConnection(DiningMainEntrance_DoorWaypoint, MainEntrance_Room);
        WaypointPathfinder.AddWaypointRoomConnection(RightWingMainEntrance_DoorWaypoint, RightWing_Room);
        WaypointPathfinder.AddWaypointRoomConnection(RightWingMainEntrance_DoorWaypoint, MainEntrance_Room);

        WaypointPathfinder.AddWaypointRoomConnection(MainEntrance_Waypoint, MainEntrance_Room);

        WaypointPathfinder.AddWaypointRoomConnection(RightWingLiving_DoorWaypoint, RightWing_Room);
        WaypointPathfinder.AddWaypointRoomConnection(RightWingLiving_DoorWaypoint, Living_Room);
        WaypointPathfinder.AddWaypointRoomConnection(RightWingFirst_Waypoint, RightWing_Room);
        WaypointPathfinder.AddWaypointRoomConnection(RightWingSecond_Waypoint, RightWing_Room);
        WaypointPathfinder.AddWaypointRoomConnection(RightWingThird_Waypoint, RightWing_Room);

        WaypointPathfinder.AddWaypointRoomConnection(RightWingStairs_DoorWaypoint, RightWing_Room);

        WaypointPathfinder.AddWaypointRoomConnection(RightWingBed_DoorWaypoint, RightWing_Room);
        WaypointPathfinder.AddWaypointRoomConnection(RightWingBed_DoorWaypoint, Bed_Room);

        WaypointPathfinder.AddWaypointRoomConnection(BedFirst_Waypoint, Bed_Room);
        WaypointPathfinder.AddWaypointRoomConnection(BedSecond_Waypoint, Bed_Room);

        WaypointPathfinder.AddWaypointRoomConnection(BedSH_DoorWaypoint, Bed_Room);
        WaypointPathfinder.AddWaypointRoomConnection(BedSH_DoorWaypoint, SH_Room);

        WaypointPathfinder.AddWaypointRoomConnection(SHFirst_Waypoint, SH_Room);
        WaypointPathfinder.AddWaypointRoomConnection(SHSecond_Waypoint, SH_Room);

        WaypointPathfinder.AddWaypointRoomConnection(SHToilet_DoorWaypoint, SH_Room);
        WaypointPathfinder.AddWaypointRoomConnection(SHToilet_DoorWaypoint, Toilet_Room);
        WaypointPathfinder.AddWaypointRoomConnection(Toilet_Waypoint, Toilet_Room);

        WaypointPathfinder.AddWaypointRoomConnection(SHLiving_DoorWaypoint, SH_Room);
        WaypointPathfinder.AddWaypointRoomConnection(SHLiving_DoorWaypoint, Living_Room);

        WaypointPathfinder.AddWaypointRoomConnection(Living_Waypoint, Living_Room);
        WaypointPathfinder.AddWaypointRoomConnection(LivingDining_DoorWaypoint, Living_Room);
        WaypointPathfinder.AddWaypointRoomConnection(LivingDining_DoorWaypoint, Dining_Room);
        
        WaypointPathfinder.AddWaypointRoomConnection(Dining_Waypoint, Dining_Room);
        WaypointPathfinder.AddWaypointRoomConnection(DiningKitchen_DoorWaypoint, Dining_Room);
        WaypointPathfinder.AddWaypointRoomConnection(DiningKitchen_DoorWaypoint, Kitchen_Room);
        WaypointPathfinder.AddWaypointRoomConnection(Kitchen_Waypoint, Kitchen_Room);

        // Adding neighbours
        WaypointPathfinder.AddNeighbour(GalleryFirst_Waypoint, GallerySecond_Waypoint);
        WaypointPathfinder.AddNeighbour(GalleryFirst_Waypoint, GalleryStudy_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(GallerySecond_Waypoint, GalleryFirst_Waypoint);
        WaypointPathfinder.AddNeighbour(GallerySecond_Waypoint, GalleryLeftWing_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(GalleryStudy_DoorWaypoint, GalleryFirst_Waypoint);
        WaypointPathfinder.AddNeighbour(GalleryStudy_DoorWaypoint, Study_Waypoint);

        WaypointPathfinder.AddNeighbour(Study_Waypoint, GalleryStudy_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(Study_Waypoint, StudyLeftWing_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(StudyLeftWing_DoorWaypoint, Study_Waypoint);
        WaypointPathfinder.AddNeighbour(StudyLeftWing_DoorWaypoint, LeftWing_Waypoint);

        WaypointPathfinder.AddNeighbour(LeftWing_Waypoint, StudyLeftWing_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(LeftWing_Waypoint, GalleryLeftWing_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(LeftWing_Waypoint, LeftWingMainEntrance_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(GalleryLeftWing_DoorWaypoint, GallerySecond_Waypoint);
        WaypointPathfinder.AddNeighbour(GalleryLeftWing_DoorWaypoint, LeftWing_Waypoint);

        WaypointPathfinder.AddNeighbour(LeftWingMainEntrance_DoorWaypoint, LeftWing_Waypoint);
        WaypointPathfinder.AddNeighbour(LeftWingMainEntrance_DoorWaypoint, MainEntrance_Waypoint);

        WaypointPathfinder.AddNeighbour(MainEntrance_Waypoint, LeftWingMainEntrance_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(MainEntrance_Waypoint, DiningMainEntrance_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(MainEntrance_Waypoint, RightWingMainEntrance_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(RightWingMainEntrance_DoorWaypoint, MainEntrance_Waypoint);
        WaypointPathfinder.AddNeighbour(RightWingMainEntrance_DoorWaypoint, RightWingFirst_Waypoint);

        WaypointPathfinder.AddNeighbour(RightWingFirst_Waypoint, RightWingMainEntrance_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(RightWingFirst_Waypoint, RightWingLiving_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(RightWingFirst_Waypoint, RightWingSecond_Waypoint);

        WaypointPathfinder.AddNeighbour(RightWingSecond_Waypoint, RightWingFirst_Waypoint);
        WaypointPathfinder.AddNeighbour(RightWingSecond_Waypoint, RightWingBed_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(RightWingSecond_Waypoint, RightWingThird_Waypoint);

        WaypointPathfinder.AddNeighbour(RightWingThird_Waypoint, RightWingSecond_Waypoint);
        WaypointPathfinder.AddNeighbour(RightWingThird_Waypoint, RightWingStairs_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(RightWingStairs_DoorWaypoint, RightWingThird_Waypoint);

        WaypointPathfinder.AddNeighbour(RightWingBed_DoorWaypoint, RightWingSecond_Waypoint);
        WaypointPathfinder.AddNeighbour(RightWingBed_DoorWaypoint, BedFirst_Waypoint);

        WaypointPathfinder.AddNeighbour(BedFirst_Waypoint, RightWingBed_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(BedFirst_Waypoint, BedSecond_Waypoint);
        WaypointPathfinder.AddNeighbour(BedFirst_Waypoint, BedSH_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(BedSecond_Waypoint, BedFirst_Waypoint);

        WaypointPathfinder.AddNeighbour(BedSH_DoorWaypoint, BedFirst_Waypoint);
        WaypointPathfinder.AddNeighbour(BedSH_DoorWaypoint, SHFirst_Waypoint);

        WaypointPathfinder.AddNeighbour(SHFirst_Waypoint, BedSH_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(SHFirst_Waypoint, SHSecond_Waypoint);
        WaypointPathfinder.AddNeighbour(SHFirst_Waypoint, SHLiving_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(SHSecond_Waypoint, SHToilet_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(SHSecond_Waypoint, SHFirst_Waypoint);
        WaypointPathfinder.AddNeighbour(SHSecond_Waypoint, SHLiving_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(SHToilet_DoorWaypoint, Toilet_Waypoint);
        WaypointPathfinder.AddNeighbour(SHToilet_DoorWaypoint, SHSecond_Waypoint);
        WaypointPathfinder.AddNeighbour(Toilet_Waypoint, SHToilet_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(SHLiving_DoorWaypoint, SHFirst_Waypoint);
        WaypointPathfinder.AddNeighbour(SHLiving_DoorWaypoint, SHSecond_Waypoint);
        WaypointPathfinder.AddNeighbour(SHLiving_DoorWaypoint, Living_Waypoint);

        WaypointPathfinder.AddNeighbour(Living_Waypoint, SHLiving_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(Living_Waypoint, RightWingLiving_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(Living_Waypoint, LivingDining_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(LivingDining_DoorWaypoint, Living_Waypoint);
        WaypointPathfinder.AddNeighbour(LivingDining_DoorWaypoint, Dining_Waypoint);

        WaypointPathfinder.AddNeighbour(Dining_Waypoint, LivingDining_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(Dining_Waypoint, DiningMainEntrance_DoorWaypoint);
        WaypointPathfinder.AddNeighbour(Dining_Waypoint, DiningKitchen_DoorWaypoint);

        WaypointPathfinder.AddNeighbour(DiningMainEntrance_DoorWaypoint, Dining_Waypoint);
        WaypointPathfinder.AddNeighbour(DiningMainEntrance_DoorWaypoint, MainEntrance_Waypoint);

        WaypointPathfinder.AddNeighbour(DiningKitchen_DoorWaypoint, Dining_Waypoint);
        WaypointPathfinder.AddNeighbour(DiningKitchen_DoorWaypoint, Kitchen_Waypoint);
        WaypointPathfinder.AddNeighbour(Kitchen_Waypoint, DiningKitchen_DoorWaypoint);

        playerMoved = true;
        timer = 5.0f;
    }
    public override void Update()
	{
        //if (playerMoved)
        //{
        //    Vector2 start = new Vector2(2320, -1000);       // monster position
        //    Vector2 goal = new Vector2(-1750, -1000);       // player position
        //    WaypointPathfinder.FindPath(start, goal);
        //    playerMoved = false;
        //    monsterPositionX = 2320;
        //    monsterPositionY = -1000;
        //}

        //Vector2 monsterPosition = WaypointPathfinder.NextStep(new Vector2(monsterPositionX, monsterPositionY), 1);
        //monsterPositionX = monsterPosition.X;
        //monsterPositionY = monsterPosition.Y;
        //Console.WriteLine(monsterPositionX + "\t\t" + monsterPositionY);
	}
 }