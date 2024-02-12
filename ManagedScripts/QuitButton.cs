using ScriptAPI;
using System;

public class QuitButton : Script
{
    public AudioComponent bgm;
    private UISpriteComponent sprite;
    bool withinArea(float mouse, float min, float max)
    {
        bool within = false;
        if (mouse > min && mouse < max)
            within = true;
        return within;
    }

    public override void Awake()
    {
       sprite = gameObject.GetComponent<UISpriteComponent>();
    }

    public override void Update()
    {


        if (Input.GetMouseButtonDown(Keycode.M1) && sprite.IsMouseCollided())
        {
            SceneLoader.LoadQuitGame();
        }
    }
}
