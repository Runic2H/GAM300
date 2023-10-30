/*!*****************************************************************************
 * \file          JoltSystem.h
 * \author        Cheang Wen Ding
 * \par DP email: cheang.w@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          30/10/2023
 * \brief         Main purpose is to linking the bodyID in rigidbody to collider
 *******************************************************************************/
#ifndef JOLTSYSTEM_H
#define JOLTSYSTEM_H

#include "dotnet/ImportExport.h"

#include "components/boxCollider.h"
#include "components/sphereCollider.h"
#include "components/capsuleCollider.h"
#include "components/rigidBody.h"


namespace TDS
{
	class DLL_API JoltSystem
	{
	public:

		static void Init();
		static void Update(const float dt, const std::vector<EntityID>& entities, 
							RigidBody* _rigidbody);
	};
}



#endif // !JOLTSYSTEM_H
