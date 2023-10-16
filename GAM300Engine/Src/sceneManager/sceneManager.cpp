/*!*************************************************************************
****
\file sceneManager.cpp
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program defines the functions in the SceneManager class
****************************************************************************
***/

#include <fstream>

#include "sceneManager/sceneManager.h"

namespace TDS
{
	// Unique pointer to instance of Scene
	std::unique_ptr<SceneManager> SceneManager::m_instance;

	/*!*************************************************************************
	Returns an instance of the SceneManager
	****************************************************************************/
	std::unique_ptr<SceneManager>& SceneManager::GetInstance()
	{
		if (m_instance == nullptr)
		{
			m_instance = std::make_unique<SceneManager>();

			std::filesystem::path currentPath = std::filesystem::current_path();
			while (!std::filesystem::exists(currentPath.string() + "\\assets"))
			{
				if (currentPath == "C:\\")
				{
					std::cout << "No asset directory found" << std::endl;
					break;
				}
				currentPath = currentPath.parent_path();
			}
			m_instance->parentFilePath = currentPath.string() + "\\assets\\";
			m_instance->filePath = currentPath.string() + "\\assets\\scenes\\";
		}
		return m_instance;
	}

	/*!*************************************************************************
	Initialize all registered components
	****************************************************************************/
	void SceneManager::Init()
	{
		ecs.registerComponent<NameTag>("Name Tag");
		ecs.registerComponent<Transform>("Transform");
		ecs.registerComponent<GraphicsComponent>("Graphics Component");
		ecs.registerComponent<AI>("AI");
		ecs.registerComponent<CameraComponent>("Camera Component");
		ecs.registerComponent<Collider>("Collider");
		ecs.registerComponent<PlayerAttributes>("Player Attributes");
		ecs.registerComponent<RigidBody>("Rigid Body");
		ecs.registerComponent<Sprite>("Sprite");
		ecs.registerComponent<Tag>("Tag");
		ecs.registerComponent<WinData>("Win Data");

		startScene = "";

		bindSystemFunctions();
		// Setting default scene
		sceneDeserialize();
	}

	/*!*************************************************************************
	Deserializes ECS entities and data from JSON file to build ECS (File loading)
	****************************************************************************/
	bool SceneManager::Deserialize(const rapidjson::Value& obj)
	{
		for (rapidjson::Value::ConstMemberIterator itr = obj["Archetype Sizes"].MemberBegin(); itr != obj["Archetype Sizes"].MemberEnd(); ++itr)
		{
			std::string archetypeID = itr->name.GetString();
			auto archetypeSizes = itr->value.GetObject();

			ecs.addArchetype(archetypeID, false);

			for (rapidjson::Value::ConstMemberIterator componentItr = archetypeSizes.MemberBegin(); componentItr != archetypeSizes.MemberEnd(); ++componentItr)
			{
				int componentID = std::stoi(componentItr->name.GetString());
				auto componentSize = componentItr->value.GetInt();

				ecs.setComponentSize(archetypeID, componentID, componentSize);
			}

			ecs.commitArchetype(archetypeID);
		}

		int i = 0;
		for (rapidjson::Value::ConstMemberIterator itr = obj["Entity Data"].MemberBegin(); itr != obj["Entity Data"].MemberEnd(); ++itr, ++i)
		{
			if (itr == obj["Entity Data"].MemberEnd())
			{
				continue;
			}

			EntityID newEntity = ecs.getNewID();
			ecs.registerEntity(newEntity);

			for (auto& m : itr->value.GetObject())
			{
				std::string componentName = m.name.GetString();

				if (componentName == "ArchetypeID") // First "componentName" to immediately find the archetype of entity
				{
					// Add all components at once
					ecs.addComponentsByArchetype(newEntity, m.value.GetString());

					continue;
				}

				auto componentData = m.value.GetObject();

				if (auto componentPointer = getComponentByName(componentName, newEntity))
				{
					componentPointer->Deserialize(componentData);
				}
			}

		}

		return true;
	}

	/*!*************************************************************************
	Serializes ECS entities and data to JSON file to save ECS (File saving)
	****************************************************************************/
	bool SceneManager::Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const
	{
		writer->StartObject();

		// Serialize archetype sizes first
		writer->String("Archetype Sizes", static_cast<rapidjson::SizeType>(std::string("Archetype Sizes").length()), false);

		writer->StartObject();

		for (Archetype* a : ecs.getAllArchetypes())
		{
			if (!a->entityIds.size())
			{
				continue;	// there is no entities under this archetype
			}

			writer->String(a->type.c_str(), static_cast<rapidjson::SizeType>(a->type.length()), false);

			// Start of data sizes
			writer->StartObject();

			for (unsigned int i = 0; i < ecs.getNumberOfComponents(); ++i)
			{
				if (a->type[i] == '1')
				{
					writer->Key(std::to_string(i).c_str());
					writer->Int(a->componentDataSize[i]);
				}
			}

			writer->EndObject();
		}

		// End of archetype sizes
		writer->EndObject();

		// =======================================================
		// Serialize entity data
		writer->String("Entity Data", static_cast<rapidjson::SizeType>(std::string("Entity Data").length()), false);
		writer->StartObject();

		std::string entityNo = "EntityNo";
		//std::string component = "Component";

		std::vector<EntityID> entityList = ecs.getEntities();

		for (int i = 0; i < entityList.size(); ++i)
		{
			writer->String(std::to_string(i).c_str(), static_cast<rapidjson::SizeType>(std::to_string(i).length()), false);
			writer->StartObject();

			std::string archetype = ecs.getArchetypeID(entityList[i]);

			writer->Key("ArchetypeID");
			writer->String(archetype.c_str());

			std::vector<std::string> componentStrings = ecs.getEntityComponents(entityList[i]);
			int j = 0;
			for (IComponent* component : ecs.getEntityComponentsBase(entityList[i]))
			{
				while (archetype[j] == '0' && j < archetype.length())
				{
					++j;
				}

				writer->String(componentStrings[j].c_str(), static_cast<rapidjson::SizeType>(componentStrings[j].length()), false);

				writer->StartObject();
				component->Serialize(writer);
				writer->EndObject();
				++j;
			}

			writer->EndObject();
		}

		// End of entity data
		writer->EndObject();

		// End of file
		writer->EndObject();

		return true;
	}

	/*!*************************************************************************
	This function serializes scenes into JSON files
	****************************************************************************/
	bool SceneManager::sceneSerialize()
	{
		std::ofstream ofs(parentFilePath + "scene.json");

		rapidjson::StringBuffer sb;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

		writer.StartObject();
		writer.String("start", 5, false);
		writer.String(startScene.c_str(), static_cast<rapidjson::SizeType>(startScene.length()), false);

		writer.EndObject();

		ofs << sb.GetString();
		ofs.flush();
		ofs.close();

		return true;
	}

	/*!*************************************************************************
	This function deserializes scenes from JSON files
	****************************************************************************/
	bool SceneManager::sceneDeserialize()
	{
		std::string allScenesFilepath = parentFilePath + "scene.json";
		std::ifstream ifs(allScenesFilepath, std::ios::in);
		std::stringstream buffer;
		buffer << ifs.rdbuf();
		ifs.close();

		rapidjson::Document doc;
		doc.Parse(buffer.str().c_str());

		if (!InitDocument(buffer.str().c_str(), doc))
		{
			return false;
		}

		rapidjson::Value& value = doc.GetObject();

		// Starting scene
		for (auto& directory_entry : std::filesystem::directory_iterator(filePath))
		{
			if (directory_entry.path().extension() == ".json")
			{
				newScene(directory_entry.path().stem().string());
			}
		}

		rapidjson::Value::MemberIterator theItr = value.FindMember("start");
		std::string startingScene = theItr->value.GetString();

		if (std::find(allScenes.begin(), allScenes.end(), startingScene) == allScenes.end())
		{
			startingScene = "";
		}

		if (startingScene == "")
		{
			if (allScenes.size() == 0)
			{
				newScene("NewScene");
				startingScene = "NewScene";
			}
			loadScene(allScenes[0]);
		}
		else
		{
			loadScene(startingScene);
		}
		currentScene = startingScene;
		startScene = startingScene;
		currentSceneSaved = true;

		return true;
	}

	bool SceneManager::stringCompare(std::string a, std::string b)
	{
		for (int index = 0; index < a.size() && index < b.size(); ++index)
		{
			char lowerA = std::tolower(a[index]);
			char lowerB = std::tolower(b[index]);

			if (lowerA < lowerB)
			{
				return true;
			}
			else if (lowerA > lowerB)
			{
				return false;
			}
		}
		if (a.size() > b.size())
		{
			return false;
		}
		return true;
	}

	/*!*************************************************************************
	This function adds a new scene into the Scene Manager
	****************************************************************************/
	void SceneManager::newScene(std::string scene)
	{
		allScenes.emplace_back(scene);

		if (!std::filesystem::exists(filePath + scene + ".json"))
		{
			std::ofstream ofs(filePath + scene + ".json");
			ofs.close();
		}

		std::sort(allScenes.begin(), allScenes.end(), stringCompare);
	}
	/*!*************************************************************************
	This function loads given scene
	****************************************************************************/
	void SceneManager::loadScene(std::string scene)
	{
		ecs.removeAllEntities();
		DeserializeFromFile(filePath + scene + ".json");
		currentScene = scene;
		currentSceneSaved = true;
	}

	/*!*************************************************************************
	This function saves the given scene 
	****************************************************************************/
	void SceneManager::saveCurrentScene()
	{
		setCurrentSceneSaved(true);

		SerializeToFile(filePath + currentScene + ".json");

		if (std::find(allScenes.begin(), allScenes.end(), currentScene) == allScenes.end())
		{
			newScene(currentScene);
		}
	}
	/*!*************************************************************************
	This function deletes the given scene
	****************************************************************************/
	void SceneManager::deleteScene(std::string scene)
	{
		if (scene == currentScene)
		{
			setCurrentSceneSaved(false);
		}

		std::filesystem::remove(filePath + scene + ".json");
		auto sceneInVector = std::find(allScenes.begin(), allScenes.end(), scene);

		if (sceneInVector != allScenes.end())
		{
			allScenes.erase(sceneInVector);
		}
	}

	/*!*************************************************************************
	This function is the getter function for current scene
	****************************************************************************/
	std::string SceneManager::getCurrentScene()
	{
		return currentScene;
	}

	/*!*************************************************************************
	This function is the setter function for current scene
	****************************************************************************/
	void SceneManager::setCurrentScene(std::string _currentScene)
	{
		currentScene = _currentScene;
	}
	/*!*************************************************************************
	This function is the getter function for current scene saved
	****************************************************************************/
	bool SceneManager::getCurrentSceneSaved()
	{
		return currentSceneSaved;
	}
	/*!*************************************************************************
	This function is the setter function for current scene saved
	****************************************************************************/
	void SceneManager::setCurrentSceneSaved(bool _currentSceneSaved)
	{
		if (!_currentSceneSaved && currentSceneSaved)
		{
			currentScene += "*";
		}
		else if (_currentSceneSaved && !currentSceneSaved)
		{
			currentScene.erase(currentScene.end() - 1);
		}

		currentSceneSaved = _currentSceneSaved;
	}

	/*!*************************************************************************
	This function renames a file
	****************************************************************************/
	bool SceneManager::renameScene(std::string oldName, std::string newName)
	{
		if (std::find(allScenes.begin(), allScenes.end(), newName) != allScenes.end())
		{
			return false;
		}

		std::filesystem::rename(filePath + oldName + ".json", filePath + newName + ".json");
		std::sort(allScenes.begin(), allScenes.end(), stringCompare);
		return true;
	}

	/*!*************************************************************************
	This function is the getter function for all scenes in Scene Browser
	****************************************************************************/
	std::vector<std::string>& SceneManager::getScenes()
	{
		return allScenes;
	}
}