using ScriptAPI;
using System;
using System.Diagnostics;
using System.Reflection;

public class GameDataManager : Script
{
    public GameData data = new GameData();
    private string file = "data.txt";
    //public GameData Data => data;

    public override void Awake()
    {
        Load();
    }

    //public override void Start()
    //{
    //    Console.WriteLine("test");
    //    Load();
    //}

    public void Save()
    {
        //string json = JsonUtility.ToJson(data);
        //WriteToFile(file, json);
        //Debug.Log("saved");
    }

    public void Load()
    {
        data = new GameData();
        string json = ReadFromFile(file);
        JsonUtility.FromJsonOverwrite(json, data);
        //Debug.Log(GetFilePath(file) + " Loaded");
    }

    private void WriteToFile(string fileName, string json)
    {
        string path = GetFilePath(fileName);
        FileStream fileStream = new FileStream(path, FileMode.Create);

        using (StreamWriter writer = new StreamWriter(fileStream))
        {
            writer.Write(json);
        }
    }

    private string ReadFromFile(string fileName)
    {
        string path = GetFilePath(fileName);
        if (File.Exists(path))
        {
            using (StreamReader reader = new StreamReader(path))
            {
                string json = reader.ReadToEnd();
                return json;
            }
        }
        else
        {
            //Debug.LogWarning("Error 404 File Not Found");
            return "";
        }
    }

    private string GetFilePath(string fileName)
    {
        return SceneLoader.dataPath + "/" + fileName;
    }
}
