/*!*************************************************************************
****
\file component.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the helper functions for component class
****************************************************************************
***/

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
	/*!*************************************************************************
	This function is a helper function to add components by string name
	****************************************************************************/
	DLL_API IComponent* addComponentByName(std::string componentName, EntityID entityID);
	/*!*************************************************************************
	This function is a helper function to get components by string name
	****************************************************************************/
	DLL_API IComponent* getComponentByName(std::string componentName, EntityID entityID);
	/*!*************************************************************************
	This function is a helper function to remove components by string name
	****************************************************************************/
	DLL_API void removeComponentByName(std::string componentName, EntityID entityID);
}

#endif