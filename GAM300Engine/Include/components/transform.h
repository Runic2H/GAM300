/*!*************************************************************************
****
\file transform.h
\author Go Ruo Yan
\par DP email: ruoyan.go@digipen.edu
\date 28-9-2023
\brief  This program declares the functions in the transform component class
****************************************************************************
***/

#ifndef TRANSFORMCOMPONENT
#define TRANSFORMCOMPONENT

#include "TDSMath.h"
#include "ecs/ecs.h"

namespace TDS
{
	class DLL_API Transform : public IComponent
	{
	public:
		/*!*************************************************************************
		Initializes the Transform component when created
		****************************************************************************/
		Transform();
		/*!*************************************************************************
		Initializes the Transform component when created, given another Transform
		component to move (for ECS)
		****************************************************************************/
		Transform(Transform&& toMove) noexcept;
		/*!*************************************************************************
		Destructor for the Transform component class
		****************************************************************************/
		~Transform() = default;
		/*!*************************************************************************
		Deserializes the WinData component
		****************************************************************************/
		virtual bool Deserialize(const rapidjson::Value& obj);
		/*!*************************************************************************
		Serializes the Transform component
		****************************************************************************/
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		/*!*************************************************************************
		Getter and setter functions for the variables in the Transform component 
		class
		****************************************************************************/
		Vec3& GetPosition() { return mPosition;  }
		void SetPosition(Vec3 position) { mPosition = position; }
		void SetPosition(float positionX, float positionY, float positionZ) { mPosition = Vec3(positionX, positionY, positionZ); }
		
		Vec3& GetScale() { return mScale; }
		void SetScale(Vec3 scale) { mScale = scale; }
		void SetScale(float scaleX, float scaleY, float scaleZ) { mScale = Vec3(scaleX, scaleY, scaleZ); }
		
		float& GetRotation() { return mRotation; }
		void SetRotation(float rotation) { mRotation = rotation; }

	private:
		Vec3 mPosition;
		Vec3 mScale;
		float mRotation;
	};
}

#endif // TRANSFORMCOMPONENT