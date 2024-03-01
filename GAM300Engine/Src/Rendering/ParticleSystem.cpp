#include "Rendering/ParticleSystem.h"

namespace TDS {



	ParticleSystem::ParticleSystem(VulkanInstance& Instance) : m_Instance(Instance) {

	}

	ParticleSystem::~ParticleSystem() {

	}

	void ParticleSystem::Init() {

	}

	void ParticleSystem::UpdateAll(float deltatime, std::vector<EntityID>& Entities, Particle_Component* Particles, Transform* Xform) {
		for (size_t i{ 0 }; i < Entities.size(); ++i) {
			UpdateEmitter(deltatime, Entities[i], &Particles[i]);
		}
	}

	void ParticleSystem::UpdateEmitter(float deltatime,EntityID ID, Particle_Component* Emitter) {
		std::uint32_t currentparticlecount = Emitter->GetCurrentParticleCount();
		std::uint32_t Desiredparticlecount = Emitter->GetDesiredParticleCount();
		if (currentparticlecount != Desiredparticlecount) {
			AddParticlestoEmitter(Emitter, Desiredparticlecount - currentparticlecount, ID);
		}
		//if amount is equal, run the update loop for the particle activity
		else {
			for (auto& particle : Emitter->GetParticleVector()) {
				if (particle.isActive) {
					particle.Age += deltatime;
					if (particle.Age >= particle.Lifetime) {
						particle.Age = 0.f;
						particle.isActive = false;
						continue;
					}
					particle.Velocity += particle.Acceleration * deltatime;//updating velocity with acceleration
					particle.Acceleration *= std::exp(-Emitter->GetDecayRate() * deltatime);//decaying acceleration per frame
					particle.Position += particle.Velocity * deltatime;//updaing particle position
				}
			}
		}
	}

	void ParticleSystem::AddParticlestoEmitter(Particle_Component* Emitter, std::uint32_t particleamount, EntityID ID) {
		Particle newparticle = Particle();
		Transform* EntityXform = ecs.getComponent<Transform>(ID);
		newparticle.Position = EntityXform->GetPosition();
		for (size_t i{ 0 }; i < particleamount; ++i) {
			Emitter->GetParticleVector().push_back(newparticle);

		}
	}
}