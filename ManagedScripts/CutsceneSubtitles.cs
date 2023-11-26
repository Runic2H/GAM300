using ScriptAPI;
using System;

public class CutsceneSubtitle : Script
{
    String[] Audiofiles;
    String[] Subtitles;
    [SerializeField]
    public static int counter;
    public override void Awake()
    {
        Audiofiles = new String[17];
        Subtitles = new String[17];
        GraphicsManagerWrapper.ToggleViewFrom2D(true);
        Subtitles[0] = "Father: My Son, if you are reading this, then I am dead,";
        Subtitles[1] = "Father: ...and I've left you with a terrible debt. But you don't have to be";
        Subtitles[2] = "Father: Your mother, God rest her soul, didn't tell us a lot about her family";
        Subtitles[3] = "Father: ...or their wealth";
        Subtitles[4] = "Father: She never mentioned them at all";

        Subtitles[5] = "Father: So imagine my surprise when I discovered their history";

        Subtitles[6] = "Father: I have seen what wealth they hold";
        Subtitles[7] = "Father: How much they have selfishly kept from us";

        Subtitles[8] = "Father: Believe me, I have tried to take what we were owed when her father died";
        Subtitles[9] = "Father: But I am not of their blood. I was always an outsider";

        Subtitles[10] = "Father: But you have their blood running within you";
        Subtitles[11] = "Father: And you deserve what was kept from you. Your rightful inheritance";

        Subtitles[12] = "Father: So my final gift to you, is simply what should have been given to you before";
        Subtitles[13] = "Father: And if they still would not give, then take it, if you must";

        Subtitles[14] = "Father: By whatever means necessary";

        Subtitles[15] = "Father: Remember, no matter what they tell you";

        Subtitles[16] = "Father: You'll always be part of the family";

        Audiofiles[0] = "Intro 1_1.mp3";
        Audiofiles[1] = "Intro 1_2.mp3";
        Audiofiles[2] = "Intro 2_1.mp3";
        Audiofiles[3] = "Intro 2_2.mp3";
        Audiofiles[4] = "Intro 2_3.mp3";
        Audiofiles[5] = "Intro 3_1.mp3";
        Audiofiles[6] = "Intro 4_1.mp3";
        Audiofiles[7] = "Intro 4_2.mp3";
        Audiofiles[8] = "Intro 5_1.mp3";
        Audiofiles[9] = "Intro 5_2.mp3";
        Audiofiles[10] = "Intro 6_1.mp3";
        Audiofiles[11] = "Intro 6_2.mp3";
        Audiofiles[12] = "Intro 7_1.mp3";
        Audiofiles[13] = "Intro 8_1.mp3";
        Audiofiles[14] = "Intro 8_2.mp3";
        Audiofiles[15] = "Intro 9_1.mp3";
        Audiofiles[16] = "Intro 9_2.mp3";

        counter = 0;
    }

    public override void Update()
    {
        if (Input.GetKeyDown(Keycode.SPACE))
        {
            GraphicsManagerWrapper.ToggleViewFrom2D(false);
            SceneLoader.LoadMainGame();
        }
        else
        {
            UISpriteComponent Sprite = gameObject.GetComponent<UISpriteComponent>();
            AudioComponent audio = gameObject.GetComponent<AudioComponent>();
      

            
            Sprite.ColorAlphafade(0.5f);
            if (Sprite.getColourAlpha() < 0)
            {
                counter++;
                if (counter > 16)//cutscene over
                {
                    GraphicsManagerWrapper.ToggleViewFrom2D(false);
                    SceneLoader.LoadMainGame();
                }
                else
                {
                    Sprite.setColourAlpha(1);
                    Sprite.SetFontMessage(Subtitles[counter]);
                }
            }
        }
    }
}