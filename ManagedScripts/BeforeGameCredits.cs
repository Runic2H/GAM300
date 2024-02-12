using ScriptAPI;
using System;

public class BeforeGameCredits : Script
{
    string[] textures;
    float counter;

    public override void Awake()
    {
        GraphicsManagerWrapper.ToggleViewFrom2D(true);
        textures = new string[2];
        textures[0] = "DigiPen Logo.dds";
        textures[1] = "GameLogoName.dds";

        counter = 0;
    }

    public override void Update()
    {
        UISpriteComponent Sprite = gameObject.GetComponent<UISpriteComponent>();
        counter += Time.deltaTime;
        
        //Console.WriteLine(counter.ToString());
        if (counter > 6.5f)
        {
            counter = 0;
        }

        if (Input.GetKeyDown(Keycode.SPACE))
        {
            SceneLoader.LoadMainMenu();
        }
        else
        {
            if(counter <= 3.0f)
            {
                Sprite.setColourAlpha(1);
                Sprite.SetTextureName(textures[0]);
            }
            if(counter > 3.0f && counter <= 6.0f)
            {
                Sprite.setColourAlpha(1);
                Sprite.SetTextureName(textures[1]);
            }

            if(counter > 6.0f)
            {
                Console.WriteLine("Switching to mainMenu");
                SceneLoader.LoadMainMenu();
            }
            
        }
    }
}
