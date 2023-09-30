#ifndef COMPONENTS
#define COMPONENTS

#include "ai.h"
#include "cameraComponent.h"
#include "collider.h"
#include "nameTag.h"
#include "playerAttributes.h"
#include "rigidBody.h"
#include "sprite.h"
#include "tag.h"
#include "transform.h"
#include "winData.h"

// Helper functions for components
namespace TDS
{
	DLL_API IComponent* addComponentByName(std::string componentName, EntityID entityID);
	DLL_API IComponent* getComponentByName(std::string componentName, EntityID entityID);
	DLL_API void removeComponentByName(std::string componentName, EntityID entityID);
}

#endif