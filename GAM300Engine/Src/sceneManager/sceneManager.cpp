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
		ECS::registerComponent<NameTag>("Name Tag");
		ECS::registerComponent<Transform>("Transform");

		ECS::registerComponent<AI>("AI");
		ECS::registerComponent<CameraComponent>("Camera Component");
		ECS::registerComponent<Collider>("Collider");
		ECS::registerComponent<PlayerAttributes>("Player Attributes");
		ECS::registerComponent<RigidBody>("Rigid Body");
		ECS::registerComponent<Sprite>("Sprite");
		ECS::registerComponent<Tag>("Tag");
		ECS::registerComponent<WinData>("Win Data");

		// Setting default scene
		//sceneDeserialize();

		allScenes.emplace_back("Game");
		allScenes.emplace_back("MainMenu");
		startScene = "MainMenu";
		currentScene = "MainMenu";

		EntityID entity1 = ECS::getNewID();
		ECS::registerEntity(entity1);
		ECS::addComponent<NameTag>(entity1);
		ECS::getComponent<NameTag>(entity1)->SetNameTag("entity1");
		ECS::addComponent<Transform>(entity1);
		ECS::getComponent<Transform>(entity1)->SetPosition(Vec3{ 2.f, 3.f, 4.f });
		ECS::getComponent<Transform>(entity1)->SetScale(Vec3{ 2.f, 3.f, 4.f });
		ECS::addComponent<AI>(entity1);
		ECS::getComponent<AI>(entity1)->SetBehaviourTreeIndex(0);

		EntityID entity2 = ECS::getNewID();
		ECS::registerEntity(entity2);
		ECS::addComponent<NameTag>(entity2);
		ECS::getComponent<NameTag>(entity2)->SetNameTag("entity2");
		ECS::addComponent<Transform>(entity2);
		ECS::getComponent<Transform>(entity2)->SetPosition(Vec3{2.f, 3.f, 4.f});
		ECS::getComponent<Transform>(entity2)->SetScale(Vec3{2.f, 3.f, 4.f});
		ECS::addComponent<Collider>(entity2);

		EntityID entity3 = ECS::getNewID();
		ECS::registerEntity(entity3);
		ECS::addComponent<NameTag>(entity3);
		ECS::getComponent<NameTag>(entity3)->SetNameTag("entity3");
		ECS::addComponent<Transform>(entity3);
		ECS::getComponent<Transform>(entity3)->SetPosition(Vec3{2.f, 3.f, 4.f});
		ECS::getComponent<Transform>(entity3)->SetScale(Vec3{2.f, 3.f, 4.f});
		ECS::addComponent<PlayerAttributes>(entity3);

		EntityID entity4 = ECS::getNewID();
		ECS::registerEntity(entity4);
		ECS::addComponent<NameTag>(entity4);
		ECS::getComponent<NameTag>(entity4)->SetNameTag("entity4");
		ECS::addComponent<Transform>(entity4);
		ECS::getComponent<Transform>(entity4)->SetPosition(Vec3{10.f, 10.f, 10.f });
		ECS::getComponent<Transform>(entity4)->SetScale(Vec3{ 10.f, 10.f, 10.f });
		ECS::addComponent<PlayerAttributes>(entity4);
		ECS::addComponent<RigidBody>(entity4);


		//for (int i = 3; i < 103; ++i)
		//{
		//	EntityID newEntity = ECS::getNewID();
		//	ECS::registerEntity(newEntity);
		//	ECS::addComponent<NameTag>(newEntity);
		//	ECS::getComponent<NameTag>(newEntity)->SetNameTag("entity" + std::to_string(i));
		//	ECS::addComponent<Transform>(newEntity);
		//	ECS::getComponent<Transform>(newEntity)->SetPosition(Vec3{ (float)i, (float)i, (float)i });
		//	ECS::getComponent<Transform>(newEntity)->SetScale(Vec3{ (float)i, (float)i, (float)i });
		//	ECS::addComponent<PlayerAttributes>(newEntity);
		//}

		//ECS::removeComponent<Transform>(entity2);


		//DeserializeFromFile(std::filesystem::current_path().parent_path().string() + "\\assets\\scenes\\" + currentScene + ".json");

		//std::cout << "ECS: " << std::endl;
		//for (auto entity : ECS::getEntities())
		//{
		//	std::cout << entity << std::endl;

		//	if (NameTag* nametag = ECS::getComponent<NameTag>(entity))
		//	{
		//		std::cout << nametag->GetNameTag() << std::endl;
		//	}
		//	if (Transform* transform = ECS::getComponent<Transform>(entity))
		//	{
		//		std::cout << transform->GetPosition() << std::endl;
		//		std::cout << transform->GetScale() << std::endl;
		//		std::cout << transform->GetRotation() << std::endl;
		//	}

		//	std::cout << std::endl;
		//}

		SerializeToFile(std::filesystem::current_path().parent_path().string() + "\\assets\\scenes\\" + currentScene + ".json");
	}

	bool SceneManager::Deserialize(const rapidjson::Value& obj)
	{
		ECS::removeAllEntities();

		for (rapidjson::Value::ConstMemberIterator itr = obj["Archetype Sizes"].MemberBegin(); itr != obj["Archetype Sizes"].MemberEnd(); ++itr)
		{
			std::string archetypeID = itr->name.GetString();
			auto archetypeSizes = itr->value.GetObject();

			ECS::addArchetype(archetypeID, false);

			for (rapidjson::Value::ConstMemberIterator componentItr = archetypeSizes.MemberBegin(); componentItr != archetypeSizes.MemberEnd(); ++componentItr)
			{
				int componentID = std::stoi(componentItr->name.GetString());
				auto componentSize = componentItr->value.GetInt();

				ECS::setComponentSize(archetypeID, componentID, componentSize);
			}

			ECS::commitArchetype(archetypeID);
		}

		int i = 0;
		for (rapidjson::Value::ConstMemberIterator itr = obj["Entity Data"].MemberBegin(); itr != obj["Entity Data"].MemberEnd(); ++itr, ++i)
		{
			if (itr == obj["Entity Data"].MemberEnd())
			{
				continue;
			}

			EntityID newEntity = ECS::getNewID();
			ECS::registerEntity(newEntity);

			for (auto& m : itr->value.GetObject())
			{
				std::string componentName = m.name.GetString();

				if (componentName == "ArchetypeID") // First "componentName" to immediately find the archetype of entity
				{
					// Add all components at once
					ECS::addComponentsByArchetype(newEntity, m.value.GetString());

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

		for (Archetype* a : ECS::getAllArchetypes())
		{
			if (!a->entityIds.size())
			{
				continue;	// there is no entities under this archetype
			}

			writer->String(a->type.c_str(), static_cast<rapidjson::SizeType>(a->type.length()), false);

			// Start of data sizes
			writer->StartObject();

			for (int i = 0; i < ECS::getNumberOfComponents(); ++i)
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

		std::vector<EntityID> entityList = ECS::getEntities();

		for (int i = 0; i < entityList.size(); ++i)
		{
			writer->String(std::to_string(i).c_str(), static_cast<rapidjson::SizeType>(std::to_string(i).length()), false);
			writer->StartObject();

			std::string archetype = ECS::getArchetypeID(entityList[i]);

			writer->Key("ArchetypeID");
			writer->String(archetype.c_str());

			std::vector<std::string> componentStrings = ECS::getEntityComponents(entityList[i]);
			int j = 0;
			for (IComponent* component : ECS::getEntityComponentsBase(entityList[i]))
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

	std::vector<std::string>& SceneManager::getScenes()
	{
		return allScenes;
	}
}