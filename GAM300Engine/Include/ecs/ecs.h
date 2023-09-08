#ifndef ECS_
#define ECS_


// reference: https://indiegamedev.net/2020/05/19/an-entity-component-system-with-data-locality-in-cpp/
namespace TDS
{
    // TYPEDEFS ===========================================================================================
    typedef std::uint32_t                   IDType;
    typedef IDType                          EntityID;
    typedef IDType                          ComponentTypeID;
    typedef std::vector<ComponentTypeID>    ArchetypeID;
    typedef unsigned char* ComponentData;

    // CONSTS =============================================================================================
    const IDType                            NULLENTITY = 0;

    // FORWARD DECLARATIONS ===============================================================================
    class                                   ECS;
    class                                   Entity;

    // TYPE ID GENERATOR CLASS ============================================================================
    // Class to generate IDs
    template<typename T>
    class TypeIdGenerator
    {
    public:
        // For each different component, the template is different, so the generates another overloaded 
        // function with a different type
        template<typename U>
        static const IDType                 getNewID();

    private:
        inline static IDType                mCount = 0;
    };

    // ARCHETYPE CLASS ====================================================================================
    // Class to differentiate the archetypes and store the entity information of each archetype
    class Archetype
    {
    public:
        // ArchetypeID - sparse vector of ComponentIDs 
        // example: if components are in the order Physics, Collision, Texture
        // an entity that has Physics and Texture will have the ArchetypeID of 101
        ArchetypeID                         type;

        // vector of pointers to the start of the data of each component
        // (data is stored by component, then entity ID, not by entityID first)
        std::vector<ComponentData>          componentData;

        // vector of sizes of each component data
        std::vector<std::size_t>            componentDataSize;

        // vector of entity IDs that are under this archetype
        // entities with Physics, and entities with Physics and Collision are under 2 different archetypes
        std::vector<EntityID>               entityIds;
    };

    // SYSTEM BASE CLASS ==================================================================================
    // Base system class for system class 
    class SystemBase
    {
    public:
        virtual                             ~SystemBase() {}

        virtual ArchetypeID                 getKey() const = 0;

        virtual void                        doAction(const float elapsedTime, Archetype* archetype) = 0;
    };

    // SYSTEM CLASS =======================================================================================
    template<class... Cs>
    class System : public SystemBase
    {
    public:
        // Making a new system
                                            System(ECS& ecs, const std::uint8_t& layer);

        // Getting the archetype ID based on the components given
        virtual ArchetypeID                 getKey() const override;

        // TYPEDEF
        typedef std::function<void(const float, const std::vector<EntityID>&, Cs*...)> 
                                            Func;

        // Setting the update function in the mFunc function pointer 
        void                                action(Func func);

    protected:
        // Filtering out the entities that satisfies the given archetype
        template<std::size_t Index1, typename T, typename... Ts>
        std::enable_if_t<Index1 != sizeof...(Cs)>
                                            doAction(const float elapsedMilliseconds,
                                                const ArchetypeID& archeTypeIds,
                                                const std::vector<EntityID>& entityIDs,
                                                T& t,
                                                Ts... ts);

        // Default function
        template<std::size_t Index1, typename T, typename... Ts>
        std::enable_if_t<Index1 == sizeof...(Cs)>
                                            doAction(const float elapsedMilliseconds,
                                                const ArchetypeID& archeTypeIds,
                                                const std::vector<EntityID>& entityIDs,
                                                T& t,
                                                Ts... ts);

        // Execute the function pointer that is set previously
        virtual void                        doAction(const float elapsedMilliseconds,
                                                Archetype* archetype) override;

        ECS& mECS;
        Func mFunc;
        bool mFuncSet;
    };

    // COMPONENT BASE CLASS ===============================================================================
    class ComponentBase
    {
    public:
        virtual                             ~ComponentBase() {}
        virtual void                        constructData(unsigned char* data) const = 0;
        virtual void                        moveData(unsigned char* source, unsigned char* destination) const = 0;
        virtual void                        destroyData(unsigned char* data) const = 0;
        virtual std::string                 getName() const = 0;
        virtual void                        setName(std::string name) = 0;
        virtual std::size_t                 getSize() const = 0;
    };

    // COMPONENT CLASS ====================================================================================
    //templated child class
    template<class C>
    class ECSComponent : public ComponentBase
    {
    public:
        // Set name of component
        virtual void                        setName(std::string name) override;

        // Get name of component
        virtual std::string                 getName() const override;

        // Allocating new memory for the data
        virtual void                        constructData(unsigned char* data) const override;

        // Destroy data of the component
        virtual void                        destroyData(unsigned char* data) const override;

        // Move the data
        virtual void                        moveData(unsigned char* source, unsigned char* destination) const override;

        // Returns the size of the whole component
        virtual std::size_t                 getSize() const override;

        // Returns the unique ID of the component
        static ComponentTypeID              getTypeID();

    private:
        std::string                         componentName;
    };

    // ECS ================================================================================================
    class ECS
    {
    private:
        // TYPEDEFS
        typedef std::unordered_map<ComponentTypeID, ComponentBase*> 
                                            ComponentTypeIDBaseMap;

        //track which entity is which archetype
        struct Record
        {
            Archetype*                      archetype;
            std::size_t                     index;
        };

        // TYPEDEFS
        typedef std::unordered_map<EntityID, Record>    
                                            EntityArchetypeMap;

        //array of all archetypes
        typedef std::vector<Archetype*>                 
                                            ArchetypesArray;


        // iterate over systems to provide a way to order system calls
        typedef std::unordered_map<std::uint8_t, std::vector<SystemBase*>>
                                            SystemsArrayMap;

    public:
        // Constructor
                                            ECS();

        // Destructor
                                            ~ECS();

        // Get new entity ID 
        EntityID                            getNewID();

        // Get the total number of systems
        int                                 getSystemCount();

        // Get the total number of systems
        template<class C>
        void                                registerComponent(std::string name);

        // Register a new system
        void                                registerSystem(const std::uint8_t& layer, SystemBase* system);

        // Register a new entity
        void                                registerEntity(const EntityID entityId);

        // Run all the systems of a certain layer
        void                                runSystems(const std::uint8_t& layer, const float elapsedMilliseconds);

        // Gets the archetype class pointer of the given archetype ID
        Archetype*                          getArchetype(const ArchetypeID& id);

        // Add a component to the entity, and (optionally) put in the values for each variable in the component
        //template<typename C, typename... Args>
        //C*                                addComponent(const EntityID& entityId, Args&&... args);

        // Add a component to the entity
        template<typename C>
        C*                                  addComponent(const EntityID& entityId);

        // Remove a component from the entity
        template<typename C>
        void                                removeComponent(const EntityID& entityId);

        // Get a component data from the entity
        template<typename C>
        C*                                  getComponent(const EntityID& entityId);

        // Get entities with a certain component in the angle bracket
        template<typename C>
        std::vector<EntityID>               getEntitiesWith();

        // Remove the entity, by removing all its component and data
        void                                removeEntity(const EntityID& entityId);

        // Remove the all of entities
        void                                removeAllEntities();

        // Set the entity ID counter
        void                                setIDCounter(int counter);

        // Getting all registered components
        std::vector<std::string>            getAllRegisteredComponents();

        // Get components of a certain entity
        std::vector<std::string>            getEntityComponents(const EntityID& entityId);

        // Getting all registered entities
        std::vector<EntityID>               getEntities();

    private:

        int                                 systemCount = 0;

        EntityArchetypeMap                  mEntityArchetypeMap;

        ArchetypesArray                     mArchetypes;

        EntityID                            mEntityIdCounter;

        SystemsArrayMap                     mSystems;

        ComponentTypeIDBaseMap              mComponentMap;
    };

    extern ECS ecs;

    // ENTITY =============================================================================================
    //wrapper for entity ID
    class Entity
    {
    public:
        // Making a new entity
        explicit                            Entity(ECS& ecs = ecs);

        // Adding a new component, with component values
        template<typename C>
        C*                                  add();

        // Adding a new component overload, move component data
        template<typename C>
        C*                                  add(C&& c);

        // Get ID of the entity
        EntityID                            getID() const;

    private:
        EntityID                            mID;
        ECS&                                mECS;
    };

    // COMPONENT ==========================================================================================
    // Base class for components
    class Component
    {
    public:
        virtual void serialize();

    private:
    };
}

#include "ecs.hpp"

#endif //ECS_
