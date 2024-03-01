using ScriptAPI;
using System;

public class FrontdoorAudio : Script
{
    String[] VO;
    AudioComponent clips;
    override public void Awake()
    {
        VO = new string[2];
        VO[0] = "pc_tryfrontdoor1";
        VO[1] = "pc_tryfrontdoor2";
    }

    override public void Start()
    {
        clips = gameObject.GetComponent<AudioComponent>();
    }

    override public void Update()
    {

    }

    public void Play(int num)
    {
        if (num - 1 >= 0)
        {
            clips.play(VO[num - 1]);
        }
    }
}