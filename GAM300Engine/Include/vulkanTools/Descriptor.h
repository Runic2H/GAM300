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


	class DLL_API DescriptorSetLayout {
	public:
		class DLL_API Builder {
		public:
			//Constructor for Descriptorsetlayout builder
			Builder(VulkanInstance& Instance) :m_Instance(Instance) {};

			//adds a binding to the descriptorset
			Builder& AddBinding(uint32_t binding, VkDescriptorType DescType, VkShaderStageFlags StageFlags, uint32_t count = 1);
			std::unique_ptr<DescriptorSetLayout>	build() const;
		private:
			VulkanInstance& m_Instance;
			std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding>	m_vBindings{};
		};
		//Constructor & destructor for Descriptorsetlayout
		DescriptorSetLayout(VulkanInstance& m_Instance, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
		~DescriptorSetLayout();

		//no copy constructor
		DescriptorSetLayout(const DescriptorSetLayout&) = delete;
		DescriptorSetLayout& operator=(const DescriptorSetLayout&) = delete;

		//getter
		VkDescriptorSetLayout getDescSetLayout() const { return m_DescSetLayout; }

	private:
		VulkanInstance& m_Instance;
		VkDescriptorSetLayout										m_DescSetLayout;
		std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding>	m_vBindings;

		friend class DescriptorWriter;
	};

	class DLL_API DescriptorPool {
	public:
		class DLL_API Builder {
		public:
			//Constructor for DescriptorPool Builder
			Builder(VulkanInstance& Instance) : m_Instance(Instance) {};

			Builder& addPoolSize(VkDescriptorType DescType, uint32_t count);
			Builder& setPoolFlags(VkDescriptorPoolCreateFlags flags);
			Builder& setMaxSets(uint32_t count);
			std::unique_ptr<DescriptorPool> build() const;

		private:
			VulkanInstance& m_Instance;
			std::vector<VkDescriptorPoolSize>	m_vPoolSizes{};
			uint32_t							m_MaxSets{ 1000 };
			VkDescriptorPoolCreateFlags			m_PoolFlags{ 0 };
		};
		//Constructor and Destructor for DescriptorPool
		DescriptorPool(VulkanInstance& Instance, uint32_t maxSets, VkDescriptorPoolCreateFlags PoolFlags, const std::vector<VkDescriptorPoolSize>& PoolSizes);
		~DescriptorPool();

		//no copy constructor
		DescriptorPool(const DescriptorPool&) = delete;
		DescriptorPool& operator=(const DescriptorPool&) = delete;

		//allocates descriptor sets into the descriptor pool
		bool allocateDescriptor(const VkDescriptorSetLayout DescSetLayout, VkDescriptorSet& Desc) const;
		//frees the descriptors in the descriptor pool
		void freeDescriptors(std::vector<VkDescriptorSet>& Descriptors)const;
		//reset the descriptors in the descriptor pool
		void resetPool();
		VkDescriptorPool getDescPool() const { return m_DescPool; }
	private:
		VulkanInstance& m_Instance;
		VkDescriptorPool	m_DescPool;

		friend class DescriptorWriter;
	};

	class DLL_API DescriptorWriter {
	public:
		//constructor for the DescriptorWriter
		DescriptorWriter(DescriptorSetLayout& setLayout, DescriptorPool& Pool);

		//writes buffer into binding
		DescriptorWriter& writeBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferinfo);
		//writes image into binding
		DescriptorWriter& writeImage(uint32_t binding, VkDescriptorImageInfo* imageinfo);

		//builds the descriptor set
		bool Build(VkDescriptorSet& set);
		//overwrite the current descriptor set
		void OverWrite(VkDescriptorSet& set);

	private:
		DescriptorSetLayout& m_SetLayout;
		DescriptorPool& m_Pool;
		std::vector<VkWriteDescriptorSet>	m_vWrites;
	};
}
#endif !TDS_VULKAN_DESCRIPTOR