using ScriptAPI;
using System;
public class DoorState : Script
{
    public enum State
    {
        Unlocked,
        Locked,
        ForcedLock
    }

    //public DoorState MainEntrance_Door;
    //public DoorState RightWingMainEntrance_Door;
    //public DoorState RightWingLiving_Door;
    //public DoorState RightWingBed_Door;
    //public DoorState BedSH_Door;
    //public DoorState SHToilet_Door;
    //public DoorState SHLivingDoor;
    //public DoorState LivingDiningDoor;
    //public DoorState DiningMainEntrance_Door;
    //public DoorState DiningKitchen_Door;
    //public DoorState LeftWingMainEntrance_Door;
    //public DoorState LeftWingGallery_Door;
    //public DoorState LeftWingStudy_Door;
    //public DoorState StudyGallery_Door;
    public State[] Doors;

    public override void Awake()
    {
        Doors = new State[13];
        for (int i = 0; i < Doors.Length; i++)
        {
            Doors[i] = State.Locked;
        }
    }
}
