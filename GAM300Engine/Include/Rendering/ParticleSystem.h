#ifndef PARTICLESYSTEM
#define PARTICLESYSTEM

#include "vulkanTools/vulkanInstance.h"
#include "vulkanTools/VulkanPipeline.h"
#include "components/ParticleComponent.h"
#include "dotnet/ImportExport.h"
#include "components/transform.h"

namespace TDS {
	

	class ParticleSystem {
	public:
		
		ParticleSystem(VulkanInstance& Instance);
		~ParticleSystem();

		ParticleSystem(const ParticleSystem&) = delete;
		ParticleSystem& operator=(const ParticleSystem&) = delete;

		void Init();
		//Update data of all particles in the scene
		void UpdateAll(float deltatime, std::vector<EntityID>& Entities, Particle_Component* Particles, Transform* Xform);
		//Spawn/Draws all particles from all entities
		void Render();

		//helper functions
		//updates the all particles tied to a single entity
		void UpdateEmitter(float deltatime,EntityID ID, Particle_Component* Emitter);
		void AddParticlestoEmitter(Particle_Component* Emitter, std::uint32_t particleamount, EntityID id);
		VulkanPipeline& GetPipeline();
	private:
		VulkanInstance& m_Instance;
		std::unique_ptr<VulkanPipeline> m_Pipeline;
		VkBuffer ParticleBuffer;
		
		uint32_t m_MaxParticles;
	};

	
}

#endif // !PARTICLESYSTEM

