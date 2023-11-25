using ScriptAPI;
using System;

public class TestSprite : Script
{
    public UISpriteComponent sprite;
    public override void Awake()
    {
        sprite = gameObject.GetComponent<UISpriteComponent>();
        Vector4 test = new Vector4();
        test.X = 1.0f;
        test.Y = 1.0f;
        test.Z = 1.0f;
        test.W = 1.0f;

        sprite.SetFontColour(test);
        sprite.SetColour(test);
        sprite.SetFontMessage("Hello");
        sprite.SetLayerID(1);
    }
    public override void OnEnable()
    {

    }
    public override void Start()
    {

    }
    public override void Update()
    {
        
    }

   


}