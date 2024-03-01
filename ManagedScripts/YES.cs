using ScriptAPI;
using System;
using System.Threading.Tasks;

public class YES : Script
{
    [SerializeField]
    public GameObject test;
    [SerializeField]
    public GameObject whateven;

    public override void Awake() 
    {

    }

    public override void OnEnable() 
    {
        Console.WriteLine("Enabled");
        //ExampleAsync();
    }

    public override void Start()
    {
        Console.WriteLine("Start Test");
    }

    public override void Update()
    {

    }

    public override void LateUpdate() { }

    public override void OnDisable() 
    {
        Console.WriteLine("Disabled");
    }

    public override void OnDestroy() 
    {
        Console.WriteLine("Exit");
    }


    // Example Usecase (Coroutine Example)
    public async IAsyncEnumerable<int> MyCoroutineAsync()
    {
        for (int i = 0; i < 5; i++)
        {
            Console.WriteLine("Coroutine step " + i);
            await Task.Delay(1000); // Simulate some work asynchronously
            yield return i;
        }
    }

    // Example Usecase
    async Task<int> ExampleAsync()
    {
        Console.WriteLine("Starting Unity Coroutine with IEnumerable result");

        await foreach (var value in Coroutine(() => MyCoroutineAsync(), 1000))
        {
            Console.WriteLine("Yielded Value: " + value);
        }

        Console.WriteLine("Unity Coroutine finished");

        return 0;
    }
}
