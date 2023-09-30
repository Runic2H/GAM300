#include "vulkanTools/Descriptor.h"
#include <cassert>

namespace TDS {
	DescriptorSetLayout::Builder& DescriptorSetLayout::Builder::AddBinding(uint32_t binding, VkDescriptorType DescType, VkShaderStageFlags StageFlags, uint32_t count) {
		assert(m_vBindings.count(binding) == 0 && "Binding already in use");
		VkDescriptorSetLayoutBinding layoutbinding{};
		layoutbinding.binding = binding;
		layoutbinding.descriptorType = DescType;
		layoutbinding.descriptorCount = count;
		layoutbinding.stageFlags = StageFlags;
		m_vBindings[binding] = layoutbinding;
		return *this;
	}

	std::unique_ptr<DescriptorSetLayout> DescriptorSetLayout::Builder::build() const {
		return std::make_unique<DescriptorSetLayout>(m_Instance, m_vBindings);
	}

	DescriptorSetLayout::DescriptorSetLayout(VulkanInstance& Instance, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings)
		: m_Instance(Instance), m_vBindings(bindings) {
		std::vector<VkDescriptorSetLayoutBinding> setLayoutBinding{};
		for (const auto& kv : m_vBindings) {
			setLayoutBinding.push_back(kv.second);
		}

		VkDescriptorSetLayoutCreateInfo descriptorsetlayoutinfo{};
		descriptorsetlayoutinfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		descriptorsetlayoutinfo.bindingCount = static_cast<uint32_t>(setLayoutBinding.size());
		descriptorsetlayoutinfo.pBindings = setLayoutBinding.data();

		if (vkCreateDescriptorSetLayout(m_Instance.getVkLogicalDevice(), &descriptorsetlayoutinfo, nullptr, &m_DescSetLayout) != VK_SUCCESS)
			throw std::runtime_error("failed to create descriptor set layout");
	}

	DescriptorSetLayout::~DescriptorSetLayout() {
		vkDestroyDescriptorSetLayout(m_Instance.getVkLogicalDevice(), m_DescSetLayout, nullptr);
	}

	// DescPoolBuider
	DescriptorPool::Builder& DescriptorPool::Builder::addPoolSize(VkDescriptorType desctype, uint32_t count) {
		m_vPoolSizes.push_back({ desctype, count });
		return *this;
	}

	DescriptorPool::Builder& DescriptorPool::Builder::setPoolFlags(VkDescriptorPoolCreateFlags flags) {
		m_PoolFlags = flags;
		return *this;
	}

	DescriptorPool::Builder& DescriptorPool::Builder::setMaxSets(uint32_t count) {
		m_MaxSets = count;
		return *this;
	}

	std::unique_ptr<DescriptorPool> DescriptorPool::Builder::build() const {
		return std::make_unique<DescriptorPool>(m_Instance, m_MaxSets, m_PoolFlags, m_vPoolSizes);
	}

	//DescPool 
	DescriptorPool::DescriptorPool(VulkanInstance& Instance, uint32_t maxset, VkDescriptorPoolCreateFlags poolFlags, const std::vector<VkDescriptorPoolSize>& Poolsize) : m_Instance(Instance) {
		VkDescriptorPoolCreateInfo descriptorpoolinfo{};
		descriptorpoolinfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		descriptorpoolinfo.poolSizeCount = static_cast<uint32_t>(Poolsize.size());
		descriptorpoolinfo.pPoolSizes = Poolsize.data();
		descriptorpoolinfo.maxSets = maxset * 4;
		descriptorpoolinfo.flags = poolFlags;

		if (vkCreateDescriptorPool(m_Instance.getVkLogicalDevice(), &descriptorpoolinfo, nullptr, &m_DescPool) != VK_SUCCESS)
			throw std::runtime_error("failed to create descriptor pool");
	}

	DescriptorPool::~DescriptorPool() {
		vkDestroyDescriptorPool(m_Instance.getVkLogicalDevice(), m_DescPool, nullptr);
	}

	bool DescriptorPool::allocateDescriptor(const VkDescriptorSetLayout descSetLayout, VkDescriptorSet& desc) const {
		VkDescriptorSetAllocateInfo allocinfo{};
		allocinfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocinfo.descriptorPool = m_DescPool;
		allocinfo.pSetLayouts = &descSetLayout;
		allocinfo.descriptorSetCount = 1;

		if (vkAllocateDescriptorSets(m_Instance.getVkLogicalDevice(), &allocinfo, &desc) != VK_SUCCESS)
			return false;
		return true;
	}

	void DescriptorPool::freeDescriptors(std::vector<VkDescriptorSet>& Descriptors) const {
		vkFreeDescriptorSets(m_Instance.getVkLogicalDevice(), m_DescPool, static_cast<uint32_t>(Descriptors.size()), Descriptors.data());
	}

	void DescriptorPool::resetPool() {
		vkResetDescriptorPool(m_Instance.getVkLogicalDevice(), m_DescPool, 0);
	}

	//DescWriter
	DescriptorWriter::DescriptorWriter(DescriptorSetLayout& setlayout, DescriptorPool& pool) : m_SetLayout(setlayout), m_Pool(pool) {};

	DescriptorWriter& DescriptorWriter::writeBuffer(uint32_t binding, VkDescriptorBufferInfo* bufferinfo) {
		assert(m_SetLayout.m_vBindings.count(binding) == 1 && "Layout does not contain specified binding");

		auto& bindingDescription = m_SetLayout.m_vBindings[binding];

		assert(bindingDescription.descriptorCount == 1 && "binding single descriptor info, but binding expects multiple");
		VkWriteDescriptorSet write{};
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorType = bindingDescription.descriptorType;
		write.dstBinding = binding;
		write.pBufferInfo = bufferinfo;
		write.descriptorCount = 1;

		m_vWrites.push_back(write);
		return *this;
	}

	DescriptorWriter& DescriptorWriter::writeImage(uint32_t binding, VkDescriptorImageInfo* imageInfo) {
		assert(m_SetLayout.m_vBindings.count(binding) == 1 && "layout does not contain specified binding");

		auto& bindingDescription = m_SetLayout.m_vBindings[binding];

		assert(bindingDescription.descriptorCount == 1 && "Binding single descriptor info, but binding expects multiple");

		VkWriteDescriptorSet write;
		write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		write.descriptorType = bindingDescription.descriptorType;
		write.dstBinding = binding;
		write.pImageInfo = imageInfo;
		write.descriptorCount = 1;

		m_vWrites.push_back(write);
		return *this;
	}

	bool DescriptorWriter::Build(VkDescriptorSet& set) {
		bool success = m_Pool.allocateDescriptor(m_SetLayout.getDescSetLayout(), set);
		if (!success)
			return false;
		OverWrite(set);
		return true;
	}

	void DescriptorWriter::OverWrite(VkDescriptorSet& set) {
		for (auto& write : m_vWrites)
			write.dstSet = set;
		vkUpdateDescriptorSets(m_Pool.m_Instance.getVkLogicalDevice(), m_vWrites.size(), m_vWrites.data(), 0, nullptr);
	}
}