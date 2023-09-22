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
		}
		return m_instance;
	}

	/*!*************************************************************************
	Initialize all registered components
	****************************************************************************/
	void SceneManager::Init()
	{
		ECS::registerComponent<NameTag>("NameTag");
		ECS::registerComponent<Transform>("Transform");

		ECS::registerComponent<CameraComponent>("CameraComponent");
		ECS::registerComponent<Collider>("Collider");
		ECS::registerComponent<PlayerAttributes>("PlayerAttributes");
		ECS::registerComponent<RigidBody>("RigidBody");
		ECS::registerComponent<Sprite>("Sprite");
		ECS::registerComponent<Tag>("Tag");
		ECS::registerComponent<WinData>("WinData");

		// Setting default scene
		//sceneDeserialize();

		//allScenes.emplace_back("Game");
		//allScenes.emplace_back("MainMenu");
		//startScene = "MainMenu";

		//EntityID entity1 = ECS::getNewID();
		//ECS::registerEntity(entity1);
		//ECS::addComponent<NameTag>(entity1);
		//ECS::getComponent<NameTag>(entity1)->SetNameTag("entity1");

		//EntityID entity2 = ECS::getNewID();
		//ECS::registerEntity(entity2);
		//ECS::addComponent<NameTag>(entity2);
		//ECS::getComponent<NameTag>(entity2)->SetNameTag("entity2");
		//ECS::addComponent<Transform>(entity2);
		//ECS::getComponent<Transform>(entity2)->SetPosition(Vec3{2.f, 3.f, 4.f});
		//ECS::getComponent<Transform>(entity2)->SetScale(Vec3{2.f, 3.f, 4.f});

		//ECS::addComponent<Transform>(entity1);

		//EntityID entity3 = ECS::getNewID();
		//ECS::registerEntity(entity3);
		//ECS::addComponent<NameTag>(entity3);
		//ECS::getComponent<NameTag>(entity3)->SetNameTag("entity3");
		//ECS::addComponent<Transform>(entity3);
		//ECS::getComponent<Transform>(entity3)->SetPosition(Vec3{ 2.f, 3.f, 4.f });
		//ECS::getComponent<Transform>(entity3)->SetScale(Vec3{ 2.f, 3.f, 4.f });
		//ECS::addComponent<PlayerAttributes>(entity3);

		
		DeserializeFromFile(std::filesystem::current_path().parent_path().string() + "\\assets\\scenes\\MainMenu.json");

		std::cout << "ECS: " << std::endl;
		for (auto entity : ECS::getEntities())
		{
			std::cout << entity << std::endl;

			if (NameTag* nametag = ECS::getComponent<NameTag>(entity))
			{
				std::cout << nametag->GetNameTag() << std::endl;
			}
			if (Transform* transform = ECS::getComponent<Transform>(entity))
			{
				std::cout << transform->GetPosition() << std::endl;
				std::cout << transform->GetScale() << std::endl;
				std::cout << transform->GetRotation() << std::endl;
			}

			std::cout << std::endl;
		}
		ECS::addComponent<Sprite>(ECS::getEntities()[0]);

		//SerializeToFile(std::filesystem::current_path().parent_path().string() + "\\assets\\scenes\\MainMenu.json");
	}

	bool SceneManager::Deserialize(const rapidjson::Value& obj)
	{
		ECS::removeAllEntities();

		//auto archetypeSizeObject = obj.MemberBegin();

		int i = 0;
		for (rapidjson::Value::ConstMemberIterator itr = obj["Entity Data"].MemberBegin(); itr != obj["Entity Data"].MemberEnd(); ++itr, ++i)
		{
			rapidjson::Value::ConstMemberIterator theItr = obj["Entity Data"].FindMember(std::to_string(i).c_str());

			if (theItr == obj["Entity Data"].MemberEnd())
			{
				continue;
			}

			auto hmmmm = theItr->name.GetString();
			auto hmm = theItr->value.GetObject();

			EntityID newEntity = ECS::getNewID();
			ECS::registerEntity(newEntity);

			for (auto& m : theItr->value.GetObject())
			{
				std::string componentName = m.name.GetString();

				if (componentName == "ArchetypeID") // First "componentName" to immediately find the archetype of entity
				{
					std::vector<ComponentTypeID> ArchetypeID;

					for (auto c : componentName)
					{
						if (c == '1')
						{
							ArchetypeID.emplace_back(1);
						}
						else
						{
							ArchetypeID.emplace_back(0);
						}
					}

					// Add all components at once

					continue;
				}

				auto componentData = m.value.GetObject();

				if (auto addedComponent = addComponentByName(componentName, newEntity))
				{
					addedComponent->Deserialize(componentData);
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
	//	writer->StartObject();

	//	// Serialize archetype sizes first
	//	writer->String("Archetype Sizes", static_cast<rapidjson::SizeType>(std::string("Archetype Sizes").length()), false);

	//	writer->StartObject();

	//	for (Archetype* a : ECS::getAllArchetypes())
	//	{
	//		if (!a->entityIds.size())
	//		{
	//			continue;	// there is no entities under this archetype
	//		}

	//		std::unordered_map<std::uint32_t, std::uint32_t> archetypeSizes;

	//		std::string archetype = "";

	//		for (int i = 0; i < ECS::getNumberOfComponents(); ++i)
	//		{
	//			if (a->componentData[i])
	//			{
	//				archetype += "1";
	//				archetypeSizes[i] = a->componentDataSize[i];
	//			}
	//			else
	//			{
	//				archetype += "0";
	//			}
	//		}

	//		writer->String(archetype.c_str(), static_cast<rapidjson::SizeType>(archetype.length()), false);

	//		// Start of data sizes
	//		writer->StartObject();

	//		for (auto archetypeSizeMap = archetypeSizes.begin(); archetypeSizeMap != archetypeSizes.end(); ++archetypeSizeMap)
	//		{
	//			writer->Key(std::to_string(archetypeSizeMap->first).c_str());
	//			writer->Int(archetypeSizeMap->second);
	//		}

	//		writer->EndObject();

	//	}

	//	// End of archetype sizes
	//	writer->EndObject();

	//	// =======================================================
	//	// Serialize entity data
	//	writer->String("Entity Data", static_cast<rapidjson::SizeType>(std::string("Entity Data").length()), false);
	//	writer->StartObject();

	//	std::string entityNo = "EntityNo";
	//	std::string component = "Component";

	//	std::vector<EntityID> entityList = ECS::getEntities();

	//	for (int i = 0; i < entityList.size(); ++i)
	//	{
	//		writer->String(std::to_string(i).c_str(), static_cast<rapidjson::SizeType>(std::to_string(i).length()), false);
	//		writer->StartObject();

	//		std::string archetypeIDString = "";
	//		for (auto componentID : ECS::getArchetypeID(entityList[i]))
	//		{
	//			archetypeIDString += std::to_string(componentID);
	//		}

	//		writer->Key("ArchetypeID");
	//		writer->String(archetypeIDString.c_str());

	//		std::vector<std::string> componentStrings = ECS::getEntityComponents(entityList[i]);
	//		int j = 0;
	//		for (IComponent* component : ECS::getEntityComponentsBase(entityList[i]))
	//		{
	//			writer->String(componentStrings[j].c_str(), static_cast<rapidjson::SizeType>(componentStrings[j].length()), false);
	//			
	//			writer->StartObject();
	//			component->Serialize(writer);
	//			writer->EndObject();

	//			++j;
	//		}

	//		writer->EndObject();
	//	}

	//	// End of entity data
	//	writer->EndObject();

	//	// End of file
	//	writer->EndObject();

		return true;
	}

	bool SceneManager::sceneSerialize()
	{
		std::ofstream ofs(std::filesystem::current_path().parent_path().string() + "\\assets\\scene.json");

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
		std::string filepath = std::filesystem::current_path().parent_path().string() + "\\assets\\scene.json";
		std::ifstream ifs(filepath, std::ios::in);
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
		DeserializeFromFile(std::filesystem::current_path().parent_path().string() + "\\assets\\scenes\\" + scene + ".json");
		currentScene = scene;
	}

	void SceneManager::saveScene(std::string scene)
	{
		SerializeToFile(std::filesystem::current_path().parent_path().string() + "\\assets\\scenes\\" + scene + ".json");
	}
	void SceneManager::deleteScene(std::string scene)
	{
		std::filesystem::remove(std::filesystem::current_path().parent_path().string() + "\\assets\\scenes\\" + scene + ".json");
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
}