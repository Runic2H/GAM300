namespace TDS
{
    // TYPE ID GENERATOR ==================================================================================
    // --getNewID--
    // Return: unique component ID
    // (for each different component, the template is different, so the generates another overloaded 
    // function with a different type)
    template<typename T>
    template<typename U>
    const IDType TypeIdGenerator<T>::getNewID()
    {
        static const IDType idCounter = mCount++;
        return idCounter;
    }

    // ENTITY =============================================================================================
    // --Entity Constructor--
    // Making a new entity
    // theecs - reference to the ECS class
    inline Entity::Entity(ECS& theecs) : mID(theecs.getNewID()), mECS(theecs)
    {
        mECS.registerEntity(mID);
    }

    // --add--
    // Adding a new component, with component values
    // Return - pointer to the entity's new component data
    template<typename C>
    inline C* Entity::add()
    {
        return mECS.addComponent<C>(mID);
    }

    // --add--
    // Adding a new component overload, move component data
    // c - component data to move
    // Return - pointer to the entity's new component data
    template<typename C>
    inline C* Entity::add(C&& c)
    {
        return mECS.addComponent<C>(mID, std::forward<C>(c));
    }

    // --getID--
    // Get ID of the entity
    // Return - entityID (from 1 onwards)
    inline EntityID Entity::getID() const
    {
        return mID;
    }

    // COMPONENT ==========================================================================================
    // --setName--
    // Set name of component
    // name - new name of component
    template<class C>
    void ECSComponent<C>::setName(std::string name)
    {
        componentName = name;
    }

    // --getName--
    // Get name of component
    // Return - name of component
    template<class C>
    std::string ECSComponent<C>::getName() const
    {
        return componentName;
    }

    // --constructData--
    // Allocating new memory for the data
    // data - pointer to the new memory for the data
    template<class C>
    void ECSComponent<C>::constructData(unsigned char* data) const
    {
        new (&data[0]) C();
    }

    // --destroyData--
    // Destroy data of the component
    // data - data to be destroyed
    template<class C>
    void ECSComponent<C>::destroyData(unsigned char* data) const
    {
        // std::launder ensures that the compiler will not flag this
        C* dataLocation = std::launder(reinterpret_cast<C*>(data));

        dataLocation->~C();
    }

    // --moveData--
    // Move the data
    // source - source of the data
    // destination - destination of the data to move to
    template<class C>
    void ECSComponent<C>::moveData(unsigned char* source, unsigned char* destination) const
    {
        new (&destination[0]) C(std::move(*reinterpret_cast<C*>(source)));
    }

    // --getSize--
    // Returns the size of the whole component
    // Return - size of the component data
    template<class C>
    std::size_t ECSComponent<C>::getSize() const
    {
        return sizeof(C);
    }

    // --getTypeID--
    // Returns the unique ID of the component
    // Return - unique ID of the component
    template<class C>
    ComponentTypeID ECSComponent<C>::getTypeID()
    {
        return TypeIdGenerator<ComponentBase>::getNewID<C>();
    }

    // SYSTEM =============================================================================================
    // --action--
    // Setting the update function in the mFunc function pointer 
    // func - update function as function pointer 
    template<class... Cs>
    void System<Cs...>::action(Func func)
    {
        mFunc = func;
        mFuncSet = true;
    }

    // --System Constructor--
    // Making a new system
    // ecs - THE ecs
    // layer - layer to put the system under
    template<class... Cs>
    System<Cs...>::System(ECS& ecs, const std::uint8_t& layer) : mECS(ecs), mFuncSet(false)
    {
        mECS.registerSystem(layer, this);
    }

    // --getKey--
    // Getting the archetype ID based on the components given
    // Return - archetype ID
    template<class... Cs>
    ArchetypeID System<Cs...>::getKey() const
    {
        return { {ECSComponent<Cs>::getTypeID()...} };
    }

    // --doAction--
    // Execute the function pointer that is set previously
    // elapsedMilliseconds - dt
    // archetype - archetype to be selected out for the function pointer to run
    template<class... Cs>
    void System<Cs...>::doAction(const float elapsedMilliseconds, Archetype* archetype)
    {
        if (mFuncSet)
            doAction<0>(elapsedMilliseconds,
                archetype->type,
                archetype->entityIds,
                archetype->componentData);
    }

    // --doAction--
    // Filtering out the entities that satisfies the given archetype
    // elapsedMilliseconds - dt
    // archeTypeIds - archetypeID to be selected out for the function pointer to run
    // entityIDs - list of entities selected
    // t & ts - components to be checked
    template<class... Cs>
    template<std::size_t Index, typename T, typename... Ts>
    std::enable_if_t<Index != sizeof...(Cs)>
        System<Cs...>::doAction(const float elapsedMilliseconds,
            const ArchetypeID& archeTypeIds,
            const std::vector<EntityID>& entityIDs,
            T& t,
            Ts... ts)
    {
        typedef std::tuple_element<Index, std::tuple<Cs...>>::type IthT;

        ComponentTypeID thisTypeCS = ECSComponent<IthT>::getTypeID();

        if (!archeTypeIds[thisTypeCS])
        {
            throw std::runtime_error
            ("System was executed against an incorrect Archetype");
        }

        doAction<Index + 1>(elapsedMilliseconds,
            archeTypeIds,
            entityIDs,
            t,
            ts...,
            reinterpret_cast<IthT*>(&t[thisTypeCS][0]));
    }

    // --doAction--
    // Default function
    // elapsedMilliseconds - dt
    // archeTypeIds - archetypeID to be selected out for the function pointer to run
    // entityIDs - list of entities selected
    // t & ts - components to be checked
    template<class... Cs>
    template<std::size_t Index, typename T, typename... Ts>
    std::enable_if_t<Index == sizeof...(Cs)>
        System<Cs...>::doAction(const float elapsedMilliseconds,
            const ArchetypeID& archeTypeIds,
            const std::vector<EntityID>& entityIDs,
            T& t,
            Ts... ts)
    {
        mFunc(elapsedMilliseconds, entityIDs, ts...);
    }

    // ECS ==========================================================================================
    // --ECS Constructor--
    inline ECS::ECS()
        :
        mEntityIdCounter(1)
    {}

    // --getNewID--
    // Get new entity ID 
    // Return - new entity ID
    inline EntityID ECS::getNewID()
    {
        return mEntityIdCounter++;
    }

    // --getSystemCount--
    // Get the total number of systems
    // Return - total number of systems
    inline int ECS::getSystemCount()
    {
        return systemCount;
    }

    // --registerComponent--
    // Register a new component
    // name - name of component
    template<class C>
    void ECS::registerComponent(std::string name)
    {
        ComponentTypeID componentTypeId = ECSComponent<C>::getTypeID();

        if (mComponentMap.contains(componentTypeId))
        {
            return; // can't re-register a type
        }

        mComponentMap.emplace(componentTypeId, new ECSComponent<C>);
        mComponentMap[componentTypeId]->setName(name);
    }

    // --registerSystem--
    // Register a new system
    // layer - layer group to put system
    // system - declared system base with a system update defined in mFunc function pointer
    inline void ECS::registerSystem(const std::uint8_t& layer, SystemBase* system)
    {
        ++systemCount;
        mSystems[layer].push_back(system);
    }

    // --registerEntity--
    // Register a new entity
    // entityId - entityID of the new entity
    inline void ECS::registerEntity(const EntityID entityId)
    {
        Record dummyRecord;
        dummyRecord.archetype = nullptr;
        dummyRecord.index = 0;
        mEntityArchetypeMap[entityId] = dummyRecord;
    }

    // --addComponent--
    // Add a component to the entity, and (optionally) put in the values for each variable in the component
    // entityId - entityID of the entity
    // Return - pointer to the entity's component data

    // args - values of the variables in the component (IN ORDER)
    //template<typename C, typename... Args>
    //inline C* ECS::addComponent(const EntityID& entityID, Args&&... args)

    template<typename C>
    inline C* ECS::addComponent(const EntityID& entityID)
    {
        // add safety checks

        ComponentTypeID newCompTypeId = ECSComponent<C>::getTypeID();

        const std::size_t& compDataSize = mComponentMap[newCompTypeId]->getSize();

        // this ensures the entity is added to dummy archetype if needed
        Record& record = mEntityArchetypeMap[entityID];
        Archetype* oldArchetype = record.archetype;

        C* newComponent = nullptr; // will be returned

        Archetype* newArchetype = nullptr;

        if (oldArchetype)
        {
            if (oldArchetype->type[newCompTypeId])
            {
                return nullptr;
            }

            // Copy the ArchetypeID to add in the new component
            ArchetypeID newArchetypeId = oldArchetype->type;
            ///newArchetypeId.push_back(newCompTypeId);
            newArchetypeId[newCompTypeId] = 1;
            ///std::sort(newArchetypeId.begin(), newArchetypeId.end());

            newArchetype = getArchetype(newArchetypeId);


            //----------------------------------------------------------------------------------REWRITE THIS
            for (std::size_t j = 0; j < newArchetypeId.size(); ++j)
            {
                if (!newArchetypeId[j])
                {
                    continue;
                }

                ///const ComponentTypeID& newCompId = newArchetypeId[j];

                const ComponentBase* const newComp = mComponentMap[j];

                const std::size_t& newCompDataSize = newComp->getSize();

                std::size_t currentSize = newArchetype->entityIds.size() * newCompDataSize;
                std::size_t newSize = currentSize + newCompDataSize;
                if (newSize > newArchetype->componentDataSize[j])
                {
                    newArchetype->componentDataSize[j] *= 2;
                    newArchetype->componentDataSize[j] += newCompDataSize;
                    unsigned char* newData = new unsigned char[newArchetype->componentDataSize[j]];
                    for (std::size_t e = 0; e < newArchetype->entityIds.size(); ++e)
                    {
                        newComp->moveData(&newArchetype->componentData[j][e * newCompDataSize],
                            &newData[e * newCompDataSize]);
                        newComp->destroyData(&newArchetype->componentData[j][e * newCompDataSize]);
                    }
                    delete[] newArchetype->componentData[j];

                    newArchetype->componentData[j] = newData;
                }

                ArchetypeID oldArchetypeId = oldArchetype->type;

                for (std::size_t i = 0; i < oldArchetype->type.size(); ++i)
                {
                    if (!(oldArchetype->type[i]))
                    {
                        continue;
                    }

                    if (i == j)
                    {
                        const ComponentBase* const oldComp = mComponentMap[i];

                        const std::size_t& oldCompDataSize = oldComp->getSize();

                        oldComp->moveData(&oldArchetype->componentData[i][record.index * oldCompDataSize],
                            &newArchetype->componentData[j][currentSize]);
                        oldComp->destroyData(&oldArchetype->componentData[i][record.index * oldCompDataSize]);

                        goto cnt;
                    }
                }

                //newComponent
                //    = new (&newArchetype->componentData[j][currentSize])
                //    C(std::forward<Args>(args)...);
                newComponent
                    = new (&newArchetype->componentData[j][currentSize])
                    C();

            cnt:;
            }

            if (!oldArchetype->entityIds.empty())
            {
                for (std::size_t i = 0; i < oldArchetype->type.size(); ++i)
                {
                    if (!(oldArchetype->type[i]))
                    {
                        continue;
                    }

                    if (i == newCompTypeId)
                    {
                        ComponentBase* removeWrapper = mComponentMap[newCompTypeId];
                        removeWrapper->destroyData(
                            &oldArchetype->componentData[i][record.index * sizeof(C)]);
                    }

                    const ComponentBase* const oldComp = mComponentMap[i];

                    const std::size_t& oldCompDataSize = oldComp->getSize();

                    //std::size_t currentSize = oldArchetype->entityIds.size() * oldCompDataSize;
                    //std::size_t newSize = currentSize - oldCompDataSize;
                    unsigned char* newData = new unsigned char[oldArchetype->componentDataSize[i] - oldCompDataSize];
                    oldArchetype->componentDataSize[i] -= oldCompDataSize;
                    for (std::size_t e = 0, ei = 0; e < oldArchetype->entityIds.size(); ++e)
                    {
                        if (e == record.index)
                            continue;

                        oldComp->moveData(&oldArchetype->componentData[i][e * oldCompDataSize],
                            &newData[ei * oldCompDataSize]);
                        oldComp->destroyData(&oldArchetype->componentData[i][e * oldCompDataSize]);

                        ++ei;
                    }

                    delete[] oldArchetype->componentData[i];

                    oldArchetype->componentData[i] = newData;
                }
            }

            std::vector<EntityID>::iterator willBeRemoved
                = std::find(oldArchetype->entityIds.begin(),
                    oldArchetype->entityIds.end(),
                    entityID);

            std::for_each(willBeRemoved, oldArchetype->entityIds.end(),
                [this, &oldArchetype](const EntityID& eid)
                {
                    Record& moveR = mEntityArchetypeMap[eid];
                    --moveR.index;
                });

            oldArchetype->entityIds.erase(willBeRemoved);
        }
        // if "archetype" in records is not created yet (new entity)
        else
        {
            ///ArchetypeID newArchetypeId(1, newCompTypeId);
            ArchetypeID newArchetypeId(systemCount, 0);
            newArchetypeId[newCompTypeId] = 1;

            const ComponentBase* const newComp = mComponentMap[newCompTypeId];

            newArchetype = getArchetype(newArchetypeId);

            std::size_t currentSize = newArchetype->entityIds.size() * compDataSize;
            std::size_t newSize = currentSize + compDataSize;
            if (newSize > newArchetype->componentDataSize[newCompTypeId])
            {
                newArchetype->componentDataSize[newCompTypeId] *= 2;
                newArchetype->componentDataSize[newCompTypeId] += compDataSize;
                unsigned char* newData = new unsigned char[newArchetype->componentDataSize[newCompTypeId]];
                for (std::size_t e = 0; e < newArchetype->entityIds.size(); ++e)
                {
                    newComp->moveData(&newArchetype->componentData[newCompTypeId][e * compDataSize],
                        &newData[e * compDataSize]);
                    newComp->destroyData(&newArchetype->componentData[newCompTypeId][e * compDataSize]);
                }
                delete[](newArchetype->componentData[newCompTypeId]);

                newArchetype->componentData[newCompTypeId] = newData;
            }

            //newComponent
            //    = new (&newArchetype->componentData[newCompTypeId][currentSize])
            //    C(std::forward<Args>(args)...);
            newComponent
                = new (&newArchetype->componentData[newCompTypeId][currentSize])
                C();
        }

        newArchetype->entityIds.push_back(entityID);
        record.index = newArchetype->entityIds.size() - 1;
        record.archetype = newArchetype;

        return newComponent;
    }

    // --removeComponent--
    // Remove a component from the entity
    // entityId - entityID of the entity
    template<class C>
    inline void ECS::removeComponent(const EntityID& entityId)
    {
        //if (!IsComponentRegistered<C>())
          //  return;

        ComponentTypeID compTypeId = ECSComponent<C>::getTypeID();

        // if (!m_entityArchetypeMap.contains(entityId))
          //   return; // it doesn't exist

        Record& record = mEntityArchetypeMap[entityId];

        Archetype* oldArchetype = record.archetype;

        if (!oldArchetype)
            return; // there's no components anyway

        if (!oldArchetype->type[compTypeId])
        {
            // this entity doesn't have this component
            return;
        }

        // find the new archetypeId by removing the old ComponentTypeId
        ArchetypeID newArchetypeId = oldArchetype->type;
        newArchetypeId[compTypeId] = 0;

        Archetype* newArchetype = getArchetype(newArchetypeId);

        for (std::size_t j = 0; j < newArchetypeId.size(); ++j)
        {
            if (!newArchetypeId[j])
            {
                continue;
            }

            const ComponentBase* const newComp = mComponentMap[(unsigned int)j];

            const std::size_t& newCompDataSize = newComp->getSize();

            std::size_t currentSize = newArchetype->entityIds.size() * newCompDataSize;
            std::size_t newSize = currentSize + newCompDataSize;
            if (newSize > newArchetype->componentDataSize[j])
            {
                newArchetype->componentDataSize[j] *= 2;
                newArchetype->componentDataSize[j] += newCompDataSize;
                unsigned char* newData = new unsigned char[newSize];
                for (std::size_t e = 0; e < newArchetype->entityIds.size(); ++e)
                {
                    newComp->moveData(&newArchetype->componentData[j][e * newCompDataSize],
                        &newData[e * newCompDataSize]);
                    newComp->destroyData(&newArchetype->componentData[j][e * newCompDataSize]);
                }
                delete[] newArchetype->componentData[j];

                newArchetype->componentData[j] = newData;
            }

            newComp->constructData(&newArchetype->componentData[j][currentSize]);

            ArchetypeID oldArchetypeId = oldArchetype->type;

            for (std::size_t i = 0; i < oldArchetype->type.size(); ++i)
            {
                if (!(oldArchetype->type[i]))
                {
                    continue;
                }

                if (i == j)
                {
                    const std::size_t& oldCompDataSize
                        = mComponentMap[(unsigned int)i]->getSize();

                    ComponentBase* removeWrapper = mComponentMap[(unsigned int)i];
                    removeWrapper->moveData(&oldArchetype->componentData[i][record.index * oldCompDataSize],
                        &newArchetype->componentData[j][currentSize]);

                    removeWrapper->destroyData(&oldArchetype->componentData[i][record.index * oldCompDataSize]);

                    break;
                }
            }
        }

        for (std::size_t i = 0; i < oldArchetype->type.size(); ++i)
        {
            if (!(oldArchetype->type[i]))
            {
                continue;
            }

            // if this is the component being removed, we should also destruct it
            if (i == compTypeId)
            {
                ComponentBase* removeWrapper = mComponentMap[compTypeId];
                removeWrapper->destroyData(
                    &oldArchetype->componentData[i][record.index * sizeof(C)]);
            }

            const ComponentBase* const oldComp = mComponentMap[(unsigned int)i];

            const std::size_t& oldCompDataSize = oldComp->getSize();

            //std::size_t currentSize = oldArchetype->entityIds.size() * oldCompDataSize;
            //std::size_t newSize = currentSize - oldCompDataSize;
            unsigned char* newData = new unsigned char[oldArchetype->componentDataSize[i] - oldCompDataSize];
            oldArchetype->componentDataSize[i] -= oldCompDataSize;
            for (std::size_t e = 0, ei = 0; e < oldArchetype->entityIds.size(); ++e)
            {
                if (e == record.index)
                    continue;

                oldComp->moveData(&oldArchetype->componentData[i][e * oldCompDataSize],
                    &newData[ei * oldCompDataSize]);
                oldComp->destroyData(&oldArchetype->componentData[i][e * oldCompDataSize]);

                ++ei;
            }

            delete[] oldArchetype->componentData[i];

            oldArchetype->componentData[i] = newData;
        }

        // each entity in the old archetypes entityIds after this one now
        // has an index 1 less
        std::vector<EntityID>::iterator willBeRemoved
            = std::find(oldArchetype->entityIds.begin(),
                oldArchetype->entityIds.end(),
                entityId);

        std::for_each(willBeRemoved, oldArchetype->entityIds.end(),
            [this, &oldArchetype](const EntityID& eid)
            {
                Record& moveR = mEntityArchetypeMap[eid];
                --moveR.index;
            });

        oldArchetype->entityIds.erase(
            std::remove(oldArchetype->entityIds.begin(),
                oldArchetype->entityIds.end(),
                entityId), oldArchetype->entityIds.end());

        newArchetype->entityIds.push_back(entityId);
        record.index = newArchetype->entityIds.size() - 1;
        record.archetype = newArchetype;
    }

    // --getComponent--
    // Get a component data from the entity
    // entityId - entityID of the entity
    // Return - pointer to the component data
    template<class C>
    inline C* ECS::getComponent(const EntityID& entityId)
    {
        ComponentTypeID compTypeId = ECSComponent<C>::getTypeID();
        if (!mEntityArchetypeMap.contains(entityId))
            return nullptr; // it doesn't exist

        Record& record = mEntityArchetypeMap[entityId];

        if (!record.archetype)
            return nullptr; // there's no components anyway

        if (!record.archetype->type[compTypeId])
            return nullptr; // this entity doesn't have this component

        return reinterpret_cast<C*>(record.archetype->componentData[compTypeId] + record.index * sizeof(C));
    }

    // --removeEntity--
    // Remove the entity, by removing all its component and data
    // entityId - entityID of the entity
    inline void ECS::removeEntity(const EntityID& entityId)
    {
        // if (!m_entityArchetypeMap.contains(entityId))
          //   return; // it doesn't exist

        Record& record = mEntityArchetypeMap[entityId];

        Archetype* oldArchetype = record.archetype;

        if (!oldArchetype)
        {
            mEntityArchetypeMap.erase(entityId);
            return; // we wouldn't know where to delete
        }

        for (std::size_t i = 0; i < oldArchetype->type.size(); ++i)
        {
            if (!oldArchetype->type[i])
            {
                continue;
            }

            const ComponentBase* const comp = mComponentMap[(unsigned int)i];

            const std::size_t& compSize = comp->getSize();

            comp->destroyData
            (&oldArchetype->componentData[i][record.index * compSize]);
        }

        for (std::size_t i = 0; i < oldArchetype->type.size(); ++i)
        {
            if (!oldArchetype->type[i])
            {
                continue;
            }

            const ComponentBase* const oldComp = mComponentMap[(unsigned int)i];

            const std::size_t& oldCompDataSize = oldComp->getSize();

            unsigned char* newData = new unsigned char[oldArchetype->componentDataSize[i] - oldCompDataSize];
            oldArchetype->componentDataSize[i] -= oldCompDataSize;
            for (std::size_t e = 0, ei = 0; e < oldArchetype->entityIds.size(); ++e)
            {
                if (e == record.index)
                    continue;

                oldComp->moveData(&oldArchetype->componentData[i][e * oldCompDataSize],
                    &newData[ei * oldCompDataSize]);

                oldComp->destroyData(&oldArchetype->componentData[i][e * oldCompDataSize]);

                ++ei;
            }

            delete[] oldArchetype->componentData[i];

            oldArchetype->componentData[i] = newData;
        }

        mEntityArchetypeMap.erase(entityId);

        std::vector<EntityID>::iterator willBeRemoved
            = std::find(oldArchetype->entityIds.begin(),
                oldArchetype->entityIds.end(),
                entityId);

        std::for_each(willBeRemoved, oldArchetype->entityIds.end(),
            [this, &oldArchetype, &entityId](const EntityID& eid)
            {
                if (eid == entityId)
                    return; // no need to adjust our removing one
                Record& moveR = mEntityArchetypeMap[eid];
                moveR.index -= 1;
            });

        oldArchetype->entityIds.erase(willBeRemoved);
    }

    // --removeAllEntities--
    // Remove the all of entities
    inline void ECS::removeAllEntities()
    {
        std::vector<EntityID> entities = ecs.getEntities();

        for (auto& i : entities)
        {
            removeEntity(i);
        }
        mEntityIdCounter = static_cast<int>(ecs.getEntities().size()) + 1;
    }

    // --setIDCounter--
    // Set the entity ID counter
    // counter - number to set the entity id counter
    inline void ECS::setIDCounter(int counter)
    {
        mEntityIdCounter = counter;
    }

    // --runSystems--
    // Run all the systems of a certain layer
    // layer - layer with all the systems to run
    // elapsedMilliseconds - dt
    inline void ECS::runSystems(const std::uint8_t& layer, const float elapsedMilliseconds)
    {
        for (SystemBase* system : mSystems[layer])
        {
            const ArchetypeID& key = system->getKey();

            for (Archetype* archetype : mArchetypes)
            {
                bool check = true;
                for (auto i : key)
                {
                    if (!(archetype->type[i]))
                    {
                        check = false;
                    }
                }

                if (check)
                {
                    // this archetype has all the types required by the system
                    // so we can pull it's relevant data, reinterpret them as
                    // their correct types, and call the Func in the system
                    system->doAction(elapsedMilliseconds, archetype);
                }
            }
        }
    }

    // --getArchetype--
    // Gets the archetype class pointer of the given archetype ID
    // id - archetype ID
    // Return - pointer to found archetype class / if not found, pointer to new archetype class
    inline Archetype* ECS::getArchetype(const ArchetypeID& id)
    {
        // Finding for archetype
        for (Archetype* archetype : mArchetypes)
        {
            if (archetype->type == id)
                return archetype;
        }

        // Archetype doesn't exist, so create a new one
        Archetype* newArchetype = new Archetype;
        newArchetype->type = id;
        mArchetypes.push_back(newArchetype);

        // Add an empty array for each component in the type
        for (ArchetypeID::size_type i = 0; i < id.size(); ++i)
        {
            if (newArchetype->type[i])
            {
                newArchetype->componentData.push_back(new unsigned char[0]);
                newArchetype->componentDataSize.push_back(1);
            }
            else
            {
                newArchetype->componentData.push_back(nullptr);
                newArchetype->componentDataSize.push_back(0);
            }
        }

        return newArchetype;
    }

    // --~ECS--
    // Decontructing ECS
    inline ECS::~ECS()
    {
        for (Archetype* archetype : mArchetypes)
        {
            for (std::size_t i = 0; i < archetype->type.size(); ++i)
            {
                if (!archetype->type[i])
                {
                    continue;
                }

                const ComponentBase* const comp = mComponentMap[(unsigned int)i];
                const std::size_t& dataSize = comp->getSize();
                for (std::size_t e = 0; e < archetype->entityIds.size(); ++e)
                {
                    comp->destroyData(&archetype->componentData[i][e * dataSize]);
                }
                delete[] archetype->componentData[i];
            }
            delete archetype;
        }
        for (ComponentTypeIDBaseMap::value_type& p : mComponentMap)
            delete p.second;
    }

    // --getAllRegisteredComponents--
    // Getting all registered components
    // Return - list of names of all the components
    inline std::vector<std::string> ECS::getAllRegisteredComponents()
    {
        std::vector<std::string> componentNames;
        for (auto i : mComponentMap)
        {
            componentNames.push_back((i.second)->getName());
        }
        return componentNames;
    }

    // --getEntities--
    // Getting all registered entities
    // Return - list of entityIDs that are valid (and not destroyed)
    inline std::vector<EntityID> ECS::getEntities()
    {
        std::vector<EntityID> entityIDs;
        for (auto i : mEntityArchetypeMap)
        {
            entityIDs.push_back(i.first);
        }
        return entityIDs;
    }

    // --getEntityComponents--
    // Get components of a certain entity
    // entityId - entityID given
    // Return - list of names of the components the entity has
    inline std::vector<std::string> ECS::getEntityComponents(const EntityID& entityId)
    {
        std::vector<std::string> components;

        Record& record = mEntityArchetypeMap[entityId];

        if (!record.archetype)
            return components; // there's no components anyway    

        for (int i = 0; i < record.archetype->type.size(); ++i)
        {
            if (!(record.archetype->type[i]))
            {
                continue;
            }

            auto it = mComponentMap.find(i);
            components.push_back(it->second->getName());
        }
        return components;
    }

    // --getEntitiesWith--
    // Get entities with a certain component in the angle bracket
    // Return - list of entityIDs
    template<class C>
    inline std::vector<EntityID> ECS::getEntitiesWith()
    {
        std::vector<EntityID> entitiesList;

        for (auto i : ecs.getEntities())
        {
            C* theType = ecs.getComponent<C>(i);
            if (theType)
            {
                entitiesList.push_back(i);
            }
        }

        return entitiesList;
    }
}
