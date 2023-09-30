#pragma once
#include "camera/camera.h"
#include "Model.h"
#include <vulkan/vulkan.h>

namespace TDS {
#define Max_Lights 10
	struct PointLight {
		Vec4 m_Position;
		Vec4 m_Color;
	};

	struct GlobalUBO {
		Mat4			m_Projection{ 1.f };
		Mat4			m_View{ 1.f };
		//Mat4			m_InverseView{1.f}; 
		Vec4			m_AmbientLightColor{ 1.f, 1.f,1.f,0.02f };
		PointLight		m_vPointLights[Max_Lights];
		//int				m_activelights;
	};

	struct FrameInfo {
		int FrameIndex;
		float FrameTime;
		VkCommandBuffer commandBuffer;
		TDSCamera camera;
		VkDescriptorSet globalDescriptorSet;
		Model& model;
		//vector of gameobj??
	};
}