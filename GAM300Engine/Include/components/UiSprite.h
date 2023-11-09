#pragma once
#include "ecs/ecs.h"
#include "ResourceManagement/ResourceManager.h"
namespace TDS
{
	class Texture;
	class UISprite : public IComponent
	{
	public:
		DLL_API UISprite();
		DLL_API UISprite(UISprite&& toMove) noexcept;
		DLL_API ~UISprite() = default;
		inline TypeReference<Texture>& GetReference()
		{
			return m_TextureReference;
		}
		DLL_API void SetPosition(Vec3& Position);
		DLL_API void SetScale(Vec3& Scale);
		DLL_API void SetRotation(Vec3& Rotation);

		DLL_API Vec3 GetPosition();
		DLL_API Vec3 GetScale();
		DLL_API Vec3 GetRotation();
		RTTR_ENABLE(IComponent);
		RTTR_REGISTRATION_FRIEND
	private:
		TypeReference<Texture>			m_TextureReference;
		Mat4 m_SpriteLocal{};
	public:
		Vec3							m_Pos = { 0.f, 0.f, 0.f };
		Vec3							m_Scale{ 1.f,1.f,1.f };
		Vec3							m_Rotation;
		bool							m_IsDirty = false;
		bool							m_EnableSprite = true;
		int								m_LayerID = -1;
		Color							m_Color;
		std::string						m_TextureName = "";


	};
}