/*!*************************************************************************
****
\file Descriptor.h
\author Ng Zuo Xian Amadeus
\par DP email: ng.z@digipen.edu
\par Course: CSD3400
\par Section: a
\date 22-9-2023
\brief  Contains the Descriptor Class and its member functions
****************************************************************************
***/
#ifndef TDS_VULKAN_DESCRIPTOR
#define TDS_VULKAN_DESCRIPTOR
#include <unordered_map>

#include "vulkanInstance.h"
#include "dotnet/ImportExport.h"
namespace TDS {


	class DescriptorSetLayout {
	public:
		class Builder {
		public:
			//Constructor for Descriptorsetlayout builder
			DLL_API Builder(VulkanInstance& Instance) :m_Instance(Instance) {};

			//adds a binding to the descriptorset
			DLL_API Builder& AddBinding(uint32_t binding, VkDescriptorType DescType, VkShaderStageFlags StageFlags, uint32_t count = 1);
			DLL_API std::unique_ptr<DescriptorSetLayout>	build() const;
		private:
			VulkanInstance& m_Instance;
			std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding>	m_vBindings{};
		};
		//Constructor & destructor for Descriptorsetlayout
		DLL_API DescriptorSetLayout(VulkanInstance& m_Instance, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
		DLL_API ~DescriptorSetLayout();

		//no copy constructor
		DLL_API DescriptorSetLayout(const DescriptorSetLayout&) = delete;
		DLL_API DescriptorSetLayout& operator=(const DescriptorSetLayout&) = delete;

		//getter
		DLL_API VkDescriptorSetLayout getDescSetLayout() const { return m_DescSetLayout; }

	private:
		VulkanInstance& m_Instance;
		VkDescriptorSetLayout										m_DescSetLayout;
		std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding>	m_vBindings;

		friend class DescriptorWriter;
	};

	class DescriptorPool {
	public:
		class Builder {
		public:
			//Constructor for DescriptorPool Builder
			DLL_API Builder(VulkanInstance& Instance) : m_Instance(Instance) {};

			DLL_API Builder& addPoolSize(VkDescriptorType DescType, uint32_t count);
			DLL_API Builder& setPoolFlags(VkDescriptorPoolCreateFlags flags);
			DLL_API Builder& setMaxSets(uint32_t count);
			DLL_API std::unique_ptr<DescriptorPool> build() const;

		private:
			VulkanInstance& m_Instance;
			std::vector<VkDescriptorPoolSize>	m_vPoolSizes{};
			uint32_t							m_MaxSets{ 1000 };
			VkDescriptorPoolCreateFlags			m_PoolFlags{ 0 };
		};
		//Constructor and Destructor for DescriptorPool
		DLL_API DescriptorPool(VulkanInstance& Instance, uint32_t maxSets, VkDescriptorPoolCreateFlags PoolFlags, const std::vector<VkDescriptorPoolSize>& PoolSizes);
		DLL_API ~DescriptorPool();

		//no copy constructor
		DLL_API DescriptorPool(const DescriptorPool&) = delete;
		DLL_API DescriptorPool& operator=(const DescriptorPool&) = delete;

		//allocates descriptor sets into the descriptor pool
		DLL_API bool allocateDescriptor(const VkDescriptorSetLayout DescSetLayout, VkDescriptorSet& Desc) const;
		//frees the descriptors in the descriptor pool
		DLL_API void freeDescriptors(std::vector<VkDescriptorSet>& Descriptors)const;
		//reset the descriptors in the descriptor pool
		DLL_API void resetPool();
		DLL_API VkDescriptorPool getDescPool() const { return m_DescPool; }
	private:
		VulkanInstance& m_Instance;
		VkDescriptorPool	m_DescPool;

		friend class DescriptorWriter;
	};

	class DescriptorWriter {
	public:
		//constructor for the DescriptorWriter
		DLL_API DescriptorWriter(DescriptorSetLayout& setLayout, DescriptorPool& Pool);

		//writes buffer into binding
		DLL_API DescriptorWriter& writeBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferinfo);
		//writes image into binding
		DLL_API DescriptorWriter& writeImage(uint32_t binding, VkDescriptorImageInfo* imageinfo);

		//builds the descriptor set
		DLL_API bool Build(VkDescriptorSet& set);
		//overwrite the current descriptor set
		DLL_API void OverWrite(VkDescriptorSet& set);

	private:
		DescriptorSetLayout& m_SetLayout;
		DescriptorPool& m_Pool;
		std::vector<VkWriteDescriptorSet>	m_vWrites;
	};
}
#endif !TDS_VULKAN_DESCRIPTOR