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
			Builder(VulkanInstance& Instance) :m_Instance(Instance) {};

			Builder& AddBinding(uint32_t binding, VkDescriptorType DescType, VkShaderStageFlags StageFlags, uint32_t count = 1);
			std::unique_ptr<DescriptorSetLayout>	build() const;
		private:
			VulkanInstance& m_Instance;
			std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding>	m_vBindings{};
		};
		DescriptorSetLayout(VulkanInstance& m_Instance, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings);
		~DescriptorSetLayout();

		DescriptorSetLayout(const DescriptorSetLayout&) = delete;
		DescriptorSetLayout& operator=(const DescriptorSetLayout&) = delete;

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

		DescriptorPool(VulkanInstance& Instance, uint32_t maxSets, VkDescriptorPoolCreateFlags PoolFlags, const std::vector<VkDescriptorPoolSize>& PoolSizes);
		~DescriptorPool();

		DescriptorPool(const DescriptorPool&) = delete;
		DescriptorPool& operator=(const DescriptorPool&) = delete;

		bool allocateDescriptor(const VkDescriptorSetLayout DescSetLayout, VkDescriptorSet& Desc) const;
		void freeDescriptors(std::vector<VkDescriptorSet>& Descriptors)const;
		void resetPool();
		VkDescriptorPool getDescPool() const { return m_DescPool; }
	private:
		VulkanInstance& m_Instance;
		VkDescriptorPool	m_DescPool;

		friend class DescriptorWriter;
	};

	class DLL_API DescriptorWriter {
	public:
		DescriptorWriter(DescriptorSetLayout& setLayout, DescriptorPool& Pool);

		DescriptorWriter& writeBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferinfo);
		DescriptorWriter& writeImage(uint32_t binding, VkDescriptorImageInfo* imageinfo);

		bool Build(VkDescriptorSet& set);
		void OverWrite(VkDescriptorSet& set);

	private:
		DescriptorSetLayout& m_SetLayout;
		DescriptorPool& m_Pool;
		std::vector<VkWriteDescriptorSet>	m_vWrites;
	};
}
#endif !TDS_VULKAN_DESCRIPTOR