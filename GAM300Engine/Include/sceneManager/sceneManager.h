#ifndef SCENEMANAGER
#define SCENEMANAGER

#include <filesystem>

#include "ecs/ecs.h"
#include "components/components.h"

namespace TDS
{
	class DLL_API SceneManager : public Serializer
	{
	public:
		/*!*************************************************************************
		Returns an instance of the SceneManager
		****************************************************************************/
		static std::unique_ptr<SceneManager>& GetInstance();

		/*!*************************************************************************
		Initialize all registered components
		****************************************************************************/
		void Init();
		/*!*************************************************************************
		Deserializes ECS entities and data from JSON file to build ECS (File loading)
		****************************************************************************/
		virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes ECS entities and data to JSON file to save ECS (File saving)
		****************************************************************************/
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		bool sceneSerialize();
		bool sceneDeserialize();

		void newScene(std::string scene);
		void loadScene(std::string scene);

		void saveScene(std::string scene);
		void deleteScene(std::string scene);

		std::string getCurrentScene();
		std::vector<std::string>& getScenes();

		bool isGameplay;

	private:
		// Unique pointer to SceneManager
		static std::unique_ptr<SceneManager> m_instance;

		std::vector<std::string> allScenes;
		std::string currentScene;
		std::string startScene;

		std::string parentFilePath;
		std::string filePath;
	};
}

#endif