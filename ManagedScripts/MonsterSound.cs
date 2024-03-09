using ScriptAPI;
using System;

public class MonsterSound : Script
{
    String[] voClips;
    AudioComponent audioPlayer;

    override public void Awake()
    {
        voClips = new String[3];
    }
    override public void Start()
    {
        audioPlayer = gameObject.GetComponent<AudioComponent>();
        voClips[0] = "pc_monstergoesaway1";
        voClips[1] = "pc_monstergoesaway2";
        voClips[2] = "pc_monsterrattledoor";
    }
    public override void Update()
    {
        
    }

    public override void OnDestroy()
    {
        audioPlayer.stopAll();
    }

    public void rattledoor()
    {
        audioPlayer.play(voClips[2]);
    }

    public void DoorMonsterSound()
    {
        audioPlayer.play(voClips[2]);
    }

    public void MosterGoesAway(int set)
    {
        audioPlayer.play(voClips[set]);
    }
}
