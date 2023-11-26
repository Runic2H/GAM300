using System;
using ScriptAPI;
using static System.Net.Mime.MediaTypeNames;

public class Hiding : Script
{
    public bool interactable;
    public bool hiding;
    public Vector3 hidingPos;
    public Vector3 nonHidingPos;
    public float _RotationAngle;
    public GameObject player;
    //public Pathfinding enemyPathfinding;
    //public Flashlight_Script _flashlight;
    public GameObject _InteractUI;
    //public CheckGameState myGameState;

    /*[Header("AudioStuff")]
    public AudioSource playerVOSource;
    public AudioClip voClip;
    public Text subtitles;*/

    bool playedAudio;
}
