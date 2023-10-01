/*!*****************************************************************************
 * \file          ResouceManager.cpp
 * \author        Eugene Ho Shu Sheng
 * \par DP email: shushengeugene.ho@digipen.edu
 * \par Course:   CSD3400
 * \par Section:  A
 * \date          01/10/2023
 * \brief         This file contains the implementation of the 
 *				  ResourceManager class.
 *******************************************************************************/
#include "ResourceManagement/ResourceManager.h"

namespace TDS
{
	ResourceManager::ResourceManager()
	{
		for (int i = 0, end = (int)m_InfoBuffer.size() - 1; i != end; ++i)
		{
			m_InfoBuffer[i].m_pData = &m_InfoBuffer[i + 1];
		}
		m_InfoBuffer[m_InfoBuffer.size() - 1].m_pData = nullptr;
		m_pEmptyBuffer = m_InfoBuffer.data();
	}

	ResourceManager::~ResourceManager()
	{
		for (auto& pair : m_ResourceInstance)
		{
			Instance_info* instance_info = pair.second;
			if (instance_info && instance_info->m_RefCount > 0)
			{
				auto it = m_AllowedTypes.find(instance_info->m_Type.m_TypeHash);
				if (it != m_AllowedTypes.end() && it->second.m_DestroyFunc)
				{
					it->second.m_DestroyFunc(instance_info->m_pData);
				}
				instance_info->m_RefCount = 0;
			}
		}

		m_ResourceInstance.clear();
		m_ResourceInUsed.clear();

		m_pEmptyBuffer = nullptr;
	}

	void* ResourceManager::GetResource(UniversalReference& uRef)
	{
		if (uRef.IsPointer()) return uRef.m_Reference;

		GuidTypeIDKey hashpair(uRef.m_GUID, uRef.m_Identifier);
		auto found = m_ResourceInstance.find(hashpair);
		if (found != m_ResourceInstance.end())
		{
			auto entry = found->second;
			++entry->m_RefCount;
			uRef.m_Reference = entry->m_pData;
			return uRef.m_Reference;
		}

		auto UniType = m_AllowedTypes.find(uRef.m_Identifier.m_TypeHash);
		assert(UniType != m_AllowedTypes.end());
		return nullptr;
	}

	void ResourceManager::ReleaseReference(UniversalReference& uRef)
	{
		if (!uRef.IsPointer() || uRef.m_GUID.GetUniqueID() == 0) return;

		auto found = m_ResourceInUsed.find(reinterpret_cast<std::uint64_t>(uRef.m_Reference));
		assert(found != m_ResourceInUsed.end());
		--found->second->m_RefCount;
		auto MainGUID = uRef.m_GUID;
		assert(uRef.m_GUID.GetUniqueID() == found->second->m_Type.m_TypeHash);
		assert(found->second->m_pData == uRef.m_Reference);

		if (found->second->m_RefCount == 0)
		{
			auto UniType = m_AllowedTypes.find(uRef.m_Identifier.m_TypeHash);
			assert(UniType != m_AllowedTypes.end());
			UniType->second.m_DestroyFunc(uRef.m_Reference);
			InstanceInfoRelease(*found->second);
		}
		uRef.m_GUID = MainGUID;

	}

	UniqueID ResourceManager::getInstanceGUID(UniversalReference& uRef) const
	{
		if (uRef.IsPointer() == false)
			return uRef.m_GUID;

		auto resource = m_ResourceInUsed.find(reinterpret_cast<std::uint64_t>(uRef.m_Reference));
		assert(resource != m_ResourceInUsed.end());

		return resource->second->m_GUID;
	}

	void ResourceManager::ReleaseResource(Instance_info& resourceInfo)
	{
		resourceInfo.m_pData = m_pEmptyBuffer;
		m_pEmptyBuffer = &resourceInfo;
	}

	Instance_info& ResourceManager::AllocResource()
	{
		auto pHead = m_pEmptyBuffer;
		assert(pHead);

		Instance_info* pNext = reinterpret_cast<Instance_info*>(m_pEmptyBuffer->m_pData);
		m_pEmptyBuffer = pNext;

		return *pHead;
	}

	void ResourceManager::InstanceInfoAlloc(void* pResourceData, UniqueID guid, TypeIdentifier typeID)
	{
		auto& rscAllocInfo = AllocResource();

		rscAllocInfo.m_pData = pResourceData;
		rscAllocInfo.m_GUID = guid;
		rscAllocInfo.m_Type = typeID;
		rscAllocInfo.m_RefCount = 1;

		m_ResourceInstance[GuidTypeIDKey(guid, typeID)] = &rscAllocInfo;
		m_ResourceInUsed[reinterpret_cast<std::uint64_t>(pResourceData)] = &rscAllocInfo;
	}

	void ResourceManager::InstanceInfoRelease(Instance_info& resourceInfo)
	{
		GuidTypeIDKey GuidID(resourceInfo.m_GUID, resourceInfo.m_Type);
		m_ResourceInstance.erase(GuidID);
		m_ResourceInUsed.erase(reinterpret_cast<std::uint64_t>(resourceInfo.m_pData));

		ReleaseResource(resourceInfo);

	}









}