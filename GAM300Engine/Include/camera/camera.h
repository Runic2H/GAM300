#ifndef TDS_CAMERA
#define TDS_CAMERA

#include "Input/Input.h"
#include "dotnet/ImportExport.h"

namespace TDS
{
	class DLL_API TDSCamera
	{
	public:

		TDSCamera(float Yaw, float pitch, Vec3 position = { 0.0f, 0.0f, 3.0f }, Vec3 up = { 0.0f, 1.0f, 0.0f });

		//using lookat and Euler Angles
		Mat4 GetViewMatrix() const;

		void UpdateCamera(float deltaTime);

		bool moving();

		float m_Fov{45.f};
	private:
		
		struct {
			bool left	{ false };
			bool right	{ false };
			bool up		{ false };
			bool down	{ false };
		}keys;
		//camera attributes
		Vec3	m_Position{};
		Vec3	m_Front{};
		Vec3	m_Up{0.f,0.f,1.f};
		Vec3	m_Right{};
		Vec3	m_Down{};
		Vec3	m_WorldUp{};

		//euler angles
		float	m_Yaw{};
		float	m_Pitch{};
		
		//option to toggle with
		float	m_Speed{1.0f};
		float	m_mouseSensitivity{0.1f}; //should it be in input???
		float	m_ZoomLevel{};
		float	m_Width{};
		float	m_Height{};

		void updateViewMatrix();
		void translate(const float& deltaWheel); // act like zoom?
		void ProcessMouseMovement(float mousex, float mousey);
	};




}//namespace TDS


#endif // !TDS_CAMERA
