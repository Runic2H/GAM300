/*!*************************************************************************
****
\file sceneManager.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the sceneManager class
****************************************************************************
***/

#ifndef SCENEMANAGER
#define SCENEMANAGER

#include <filesystem>

#include "ecs/ecs.h"
#include "components/components.h"

namespace TDS
{
	class SceneManager : public Serializer
	{
	public:
		/*!*************************************************************************
		Returns an instance of the SceneManager
		****************************************************************************/
		DLL_API static std::unique_ptr<SceneManager>& GetInstance();

		/*!*************************************************************************
		Initialize all registered components
		****************************************************************************/
		DLL_API void Init();
		/*!*************************************************************************
		Deserializes ECS entities and data from JSON file to build ECS (File loading)
		****************************************************************************/
		DLL_API virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes ECS entities and data to JSON file to save ECS (File saving)
		****************************************************************************/
		DLL_API virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		This function serializes scenes into JSON files
		****************************************************************************/
		DLL_API bool sceneSerialize();
		/*!*************************************************************************
		This function deserializes scenes from JSON files
		****************************************************************************/
		DLL_API bool sceneDeserialize();

		/*!*************************************************************************
		This function adds a new scene into the Scene Manager
		****************************************************************************/
		DLL_API void newScene(std::string scene);
		/*!*************************************************************************
		This function loads given scene
		****************************************************************************/
		DLL_API void loadScene(std::string scene);

		/*!*************************************************************************
		This function saves the given scene
		****************************************************************************/
		DLL_API void saveScene(std::string scene);
		/*!*************************************************************************
		This function deletes the given scene
		****************************************************************************/
		DLL_API void deleteScene(std::string scene);

		/*!*************************************************************************
		This function is the getter function for current scene
		****************************************************************************/
		DLL_API std::string getCurrentScene();
		/*!*************************************************************************
		This function is the getter function for all scenes in Scene Browser
		****************************************************************************/
		DLL_API std::vector<std::string>& getScenes();

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