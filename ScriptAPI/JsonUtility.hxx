
namespace ScriptAPI
{
	public ref class JsonUtility
	{
	public:
		static void FromJsonOverwrite(System::String^ json, Object^ data);
		static System::String^ ToJson(Object^ data);
	};
}