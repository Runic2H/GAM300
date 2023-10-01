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

		ecs.registerComponent<AI>("AI");
		ecs.registerComponent<CameraComponent>("Camera Component");
		ecs.registerComponent<Collider>("Collider");
		ecs.registerComponent<PlayerAttributes>("Player Attributes");
		ecs.registerComponent<RigidBody>("Rigid Body");
		ecs.registerComponent<Sprite>("Sprite");
		ecs.registerComponent<Tag>("Tag");
		ecs.registerComponent<WinData>("Win Data");

		bindSystemFunctions();

		// Setting default scene
		sceneDeserialize();

		//allScenes.emplace_back("Game");
		//allScenes.emplace_back("MainMenu");
		//startScene = "MainMenu";
		//currentScene = "MainMenu";

		//EntityID entity1 = ecs.getNewID();
		//ecs.registerEntity(entity1);
		//ecs.addComponent<NameTag>(entity1);
		//ecs.getComponent<NameTag>(entity1)->SetNameTag("entity1");
		//ecs.addComponent<Transform>(entity1);
		//ecs.getComponent<Transform>(entity1)->SetPosition(Vec3{ 2.f, 3.f, 4.f });
		//ecs.getComponent<Transform>(entity1)->SetScale(Vec3{ 2.f, 3.f, 4.f });
		//ecs.addComponent<AI>(entity1);
		//ecs.getComponent<AI>(entity1)->SetBehaviourTreeIndex(0);

		//EntityID entity2 = ecs.getNewID();
		//ecs.registerEntity(entity2);
		//ecs.addComponent<NameTag>(entity2);
		//ecs.getComponent<NameTag>(entity2)->SetNameTag("entity2");
		//ecs.addComponent<Transform>(entity2);
		//ecs.getComponent<Transform>(entity2)->SetPosition(Vec3{2.f, 3.f, 4.f});
		//ecs.getComponent<Transform>(entity2)->SetScale(Vec3{2.f, 3.f, 4.f});
		//ecs.addComponent<Collider>(entity2);

		//EntityID entity3 = ecs.getNewID();
		//ecs.registerEntity(entity3);
		//ecs.addComponent<NameTag>(entity3);
		//ecs.getComponent<NameTag>(entity3)->SetNameTag("entity3");
		//ecs.addComponent<Transform>(entity3);
		//ecs.getComponent<Transform>(entity3)->SetPosition(Vec3{2.f, 3.f, 4.f});
		//ecs.getComponent<Transform>(entity3)->SetScale(Vec3{2.f, 3.f, 4.f});
		//ecs.addComponent<PlayerAttributes>(entity3);

		//EntityID entity4 = ecs.getNewID();
		//ecs.registerEntity(entity4);
		//ecs.addComponent<NameTag>(entity4);
		//ecs.getComponent<NameTag>(entity4)->SetNameTag("entity4");
		//ecs.addComponent<Transform>(entity4);
		//ecs.getComponent<Transform>(entity4)->SetPosition(Vec3{10.f, 10.f, 10.f });
		//ecs.getComponent<Transform>(entity4)->SetScale(Vec3{ 10.f, 10.f, 10.f });
		//ecs.addComponent<PlayerAttributes>(entity4);
		//ecs.addComponent<RigidBody>(entity4);


		//for (int i = 3; i < 103; ++i)
		//{
		//	EntityID newEntity = ecs.getNewID();
		//	ecs.registerEntity(newEntity);
		//	ecs.addComponent<NameTag>(newEntity);
		//	ecs.getComponent<NameTag>(newEntity)->SetNameTag("entity" + std::to_string(i));
		//	ecs.addComponent<Transform>(newEntity);
		//	ecs.getComponent<Transform>(newEntity)->SetPosition(Vec3{ (float)i, (float)i, (float)i });
		//	ecs.getComponent<Transform>(newEntity)->SetScale(Vec3{ (float)i, (float)i, (float)i });
		//	ecs.addComponent<PlayerAttributes>(newEntity);
		//}

		//ecs.removeComponent<Transform>(entity2);


		//DeserializeFromFile(std::filesystem::current_path().parent_path().string() + "\\assets\\scenes\\" + currentScene + ".json");

		//std::cout << "ECS: " << std::endl;
		//for (auto entity : ecs.getEntities())
		//{
		//	std::cout << entity << std::endl;

		//	if (NameTag* nametag = ecs.getComponent<NameTag>(entity))
		//	{
		//		std::cout << nametag->GetNameTag() << std::endl;
		//	}
		//	if (Transform* transform = ecs.getComponent<Transform>(entity))
		//	{
		//		std::cout << transform->GetPosition() << std::endl;
		//		std::cout << transform->GetScale() << std::endl;
		//		std::cout << transform->GetRotation() << std::endl;
		//	}

		//	std::cout << std::endl;
		//}

		//SerializeToFile(filePath + currentScene + ".json");
	}

	bool SceneManager::Deserialize(const rapidjson::Value& obj)
	{
		ecs.removeAllEntities();

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

			for (int i = 0; i < ecs.getNumberOfComponents(); ++i)
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
		std::string component = "Component";

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

	bool SceneManager::sceneSerialize()
	{
		std::ofstream ofs(parentFilePath + "scene.json");

		rapidjson::StringBuffer sb;
		rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(sb);

		writer.StartObject();

		for (int i = 0; i < allScenes.size(); ++i)
		{
			if (allScenes[i] == startScene)
			{
				writer.String("start", 5, false);
			}
			else
			{
				writer.String(std::to_string(i + 1).c_str(), static_cast<rapidjson::SizeType>(std::to_string(i + 1).length()), false);
			}
			writer.String(allScenes[i].c_str(), static_cast<rapidjson::SizeType>(allScenes[i].length()), false);
		}
		writer.EndObject();

		ofs << sb.GetString();
		ofs.flush();
		ofs.close();

		return true;
	}

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
		rapidjson::Value::MemberIterator theItr = value.FindMember("start");

		std::string startingScene = theItr->value.GetString();

		SceneManager::newScene(startingScene);

		int i = 0;
		for (rapidjson::Value::ConstMemberIterator itr = value.MemberBegin(); itr != value.MemberEnd(); ++itr, ++i)
		{
			theItr = value.FindMember(std::to_string(i + 1).c_str());

			if (!value.HasMember(std::to_string(i + 1).c_str()))
			{
				continue;
			}

			SceneManager::newScene(theItr->value.GetString());
		}

		SceneManager::loadScene(startingScene);
		currentScene = startingScene;
		startScene = startingScene;

		return true;
	}

	void SceneManager::newScene(std::string scene)
	{
		allScenes.emplace_back(scene);
	}
	void SceneManager::loadScene(std::string scene)
	{
		DeserializeFromFile(filePath + scene + ".json");
		currentScene = scene;
	}

	void SceneManager::saveScene(std::string scene)
	{
		SerializeToFile(filePath + scene + ".json");
	}
	void SceneManager::deleteScene(std::string scene)
	{
		std::filesystem::remove(filePath + scene + ".json");
		auto sceneInVector = std::find(allScenes.begin(), allScenes.end(), scene);

		if (sceneInVector != allScenes.end())
		{
			allScenes.erase(sceneInVector);
		}
	}

	std::string SceneManager::getCurrentScene()
	{
		return currentScene;
	}

	std::vector<std::string>& SceneManager::getScenes()
	{
		return allScenes;
	}
}