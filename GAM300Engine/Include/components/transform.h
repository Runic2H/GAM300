#ifndef TRANSFORMCOMPONENT
#define TRANSFORMCOMPONENT

#include "TDSMath.h"
#include "ecs/ecs.h"

namespace TDS
{
	class Transform : public IComponent
	{
	public:
		Transform();
		~Transform() = default;
		virtual bool Deserialize(const rapidjson::Value& obj);
		virtual bool Serialize(rapidjson::PrettyWriter<rapidjson::StringBuffer>* writer) const;

		virtual void ImGuiDisplay();

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