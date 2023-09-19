#ifndef VULKAN_CREATE_INSTANCE
#define VULKAN_CREATE_INSTANCE

#ifndef NOMINMAX
#define NOMINMAX
#endif//NOMINMAX
#define	VK_USE_PLATFORM_WIN32_KHR

#include <vulkan/vulkan.h>
#include <vector>
#include <string>
#include <iostream>
#include <set>
#include <limits>
#include <algorithm>
#include <fstream>
#include <optional>
#include <array>
#include <chrono>//to be moved

//assimp to be moved
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
//assimp
#include "windowswindow.h"
#include "vulkanTools/vulkanDebugger.h"
#include "vulkanTools/vulkanDevice.h"
#include "TDSMath.h"
//#include "vulkanSwapChain.h"
#include "Vector2.h"
#include "dotnet/ImportExport.h"
#include "camera/camera.h"
namespace TDS
{
	
	class /*DLL_API*/ VulkanInstance
	{

		static std::vector<char> readFile(const std::string& filename) 
		{
			std::ifstream file(filename, std::ios::ate | std::ios::binary);

			if (!file.is_open()) {
				throw std::runtime_error("failed to open file!");
			}

			size_t fileSize = (size_t)file.tellg();
			std::vector<char> buffer(fileSize);

			file.seekg(0);
			file.read(buffer.data(), fileSize);

			file.close();

			return buffer;

		}

		struct QueueFamilyIndices
		{
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t>	presentFamily;
			bool isComplete()
			{
				return graphicsFamily.has_value() &&
					   presentFamily.has_value();
			}
		};
		struct SwapChainSupportDetails
		{
			VkSurfaceCapabilitiesKHR capabilities{};
			std::vector<VkSurfaceFormatKHR> formats{};
			std::vector<VkPresentModeKHR> presentModes{};
		};
		struct Vertex
		{
			Vec3 pos;
			Vec3 color;
			Vec2 texCoord;
			static VkVertexInputBindingDescription getBindingDescription() 
			{
				VkVertexInputBindingDescription bindingDescription{};
				bindingDescription.binding = 0;
				bindingDescription.stride = sizeof(Vertex);
				bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; //or can per instance (VK_VERTEX_INPUT_RATE_INSTANCE)

				return bindingDescription;
			}
			static std::array<VkVertexInputAttributeDescription, 3> getAttributeDescriptions() 
			{
				std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};
				//pos which now is vec 2
				attributeDescriptions[0].binding = 0;
				attributeDescriptions[0].location = 0;
				attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT; //r32g32 using 2 floats
				attributeDescriptions[0].offset = offsetof(Vertex, pos);

				//color which now is vec3
				attributeDescriptions[1].binding = 0;
				attributeDescriptions[1].location = 1;
				attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;//using 3 floats
				attributeDescriptions[1].offset = offsetof(Vertex, color);

				attributeDescriptions[2].binding = 0;
				attributeDescriptions[2].location = 2;
				attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
				attributeDescriptions[2].offset = offsetof(Vertex, texCoord);

				return attributeDescriptions;
			}
			
		};
		struct UniformBufferObject
		{
			Mat4 model;
			Mat4 view;
			Mat4 proj;
		};

	public://functions

		VulkanInstance(const  WindowsWin& enableWindows);
		~VulkanInstance();
		VkResult createInstance(bool enableValidation);
		void	 drawFrame(const WindowsWin& _Windows, float deltaTime);
		//getters
		//VkInstance		 getVkInstance()const		{ return m_VKhandler; }
		//VkPhysicalDevice getVkPhysicalDevice()const { return m_PhysDeviceHandle; }
		VkDevice		 getVkLogicalDevice()const { return m_logicalDevice; }
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	private:

		bool			   checkValidationLayerSupport();
		bool			   isDeviceSuitable(VkPhysicalDevice device);

		//to be moved to other file
		bool					 checkDeviceExtensionSupport(VkPhysicalDevice device);
		SwapChainSupportDetails  querySwapChainSupport(const VkPhysicalDevice& device);
		VkSurfaceFormatKHR		 chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR         chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D				 chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities, const WindowsWin& windows);
		VkShaderModule			 createShaderModule(const std::vector<char>& code);
		void					 recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
	
		void					 recreateSwapChain(const WindowsWin& _Windows);
		void					 createSwapChain(const WindowsWin& _Windows);
		void					 cleanupSwapChain();
		void					 createImageViews();
		void					 createFrameBuffer();
		
		//to be removed
		void					 createBuffers(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer,
											   VkDeviceMemory& buffermemory);
		void					 createVertexBuffer();
		void					 createIndexBuffer();
		void					 createUniformBuffers();
		void					 createDescriptorPool();
		void					 createDescriptorSets();
		uint32_t				 findMemoryType(const uint32_t& typeFiler, VkMemoryPropertyFlags properties);
		void					 copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

		//provide details about every descriptor binding used in the shaders for pipeline creation
		void					 createDescriptorSetLayout();

		//to be removed
		void					 updateUniformBuffer(uint32_t currentImage, float deltaTime);


		//texture loading thingy
		void					 createTextureImage();
		void					 createImage(uint32_t width, uint32_t height, uint32_t miplevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling,
								 VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
		void					 createTextureSampler();
		

		//mipmap
		void					 generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
		//depth buffer
		void					 createDepthResource();
		void					 createColorResource();

		//load models obj
		void					 loadModel();
		//helper function to process the aiscene
		void					 processNode(aiNode* node, const aiScene* scene);

		void					 processMesh(aiMesh* mesh, const aiScene* scene);
public:
		//helper function
		VkCommandBuffer			 beginSingleTimeCommands();
		VkImageView				 createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectflags, uint32_t mipmaps);
		void					 endSingleTimeCommands(VkCommandBuffer commandBuffer);
		void					 transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipmaps);
		void					 copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
		void					 createTextureImageView();


		//helper function to find the most to less desirable depth format
		VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
		VkFormat findDepthFormat();
		bool	 hasStencilComponent(VkFormat format); //to tell if chose depth formats comes with stencil component?
	
		//query on max sample bit we can use
		VkSampleCountFlagBits	 getMaxUsableSampleCount();


public://members

		static constexpr decltype(VkApplicationInfo::apiVersion) apiVersion		{ VK_API_VERSION_1_3 };
		std::vector<std::string> supportedInstanceExtensions{};
		std::vector<const char*> enabledInstanceExtensions{};

		bool framebufferResized { false };
	
	public:

		//frames processed concurrently
		const int MAX_FRAMES_IN_FLIGHT { 2 };	//maybe set as a macro, will see

		uint32_t  m_currentFrame{ 0 }; //keep track to make sure using the right objects every frame

		VkDescriptorPool			  m_ImguiDescriptorPool;

		/*Each frame should have its own command buffer, set of semaphores, and fence*/
		std::vector <VkCommandBuffer> m_commandBuffers;
		std::vector <VkSemaphore>	  m_imageAvailableSemaphore;
		std::vector <VkSemaphore>	  m_renderFinishedSemaphore;
		std::vector <VkFence>		  m_inFlightFence;

	
		std::vector<VkImageView> swapChainImageViews;
		VkInstance				m_VKhandler;
		VkPhysicalDevice		m_PhysDeviceHandle{ VK_NULL_HANDLE }; //where selected graphic card is stored
		VkDevice				m_logicalDevice;
		VkQueue					m_graphicQueue;	
		VkQueue					m_presentQueue;
		VkSurfaceKHR			m_Surface{};
		VkSwapchainKHR			m_SwapChain{};
		VkFormat				m_swapChainImageFormat;
		VkExtent2D				m_swapChainExtent;
		VkSurfaceFormatKHR		m_VKSurfaceFormat{};
		VkRenderPass			m_RenderPass;
		VkDescriptorSetLayout	m_descriptorSetLayout;
		VkPipelineLayout		m_pipelineLayout;
		VkPipeline				m_graphicPipeline;
		VkCommandPool			m_commandPool;

		//handle vertex
		VkBuffer			m_vertexBuffer; //use it in rendering commands, does not depend on swapchain
		VkDeviceMemory		m_vertexBufferMemory;// store the handle to the memory 

		//handle indices
		VkBuffer			m_indexBuffer;
		VkDeviceMemory		m_IndexBufferMemory;

		//handle uniform buffers
		//copy new data to the uniform buffer every frame
		std::vector<VkBuffer>		uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<void*>			uniformBuffersMapped;

		VkDescriptorPool			 m_descriptorPool;
		std::vector<VkDescriptorSet> m_descriptorSets;

		//texture
		uint32_t					 m_mipLevels; //precalculated : level 0 is original image anything above it is reffered to as mip chain
		VkImage						 m_textureImage;
		VkDeviceMemory				 m_textureImageMemory;
		VkImageView					 m_textureImageView;
		VkSampler					 m_textureSampler;

		//depthBuffer thing
		VkImage						 m_depthImage;
		VkDeviceMemory				 m_depthImageMemory;
		VkImageView					 m_depthImageView;

		//multi sampling anti-aliasing aka remove the stairs effect
		VkSampleCountFlagBits		 m_msaaSamples { VK_SAMPLE_COUNT_1_BIT }; //1 bit = no msaa
		VkImage						 m_colorImage;
		VkDeviceMemory				 m_colorImageMemory;
		VkImageView					 m_colorImageView;

		std::vector<VkImage>		   m_swapChainImages;
		std::vector<VkFramebuffer>	   m_swapChainFramebuffers;
		const std::vector<const char*> validationLayers { "VK_LAYER_KHRONOS_validation" };
		const std::vector<const char*> deviceExtensions { VK_KHR_SWAPCHAIN_EXTENSION_NAME };
		std::vector <VkPipelineShaderStageCreateInfo> shaderStages{};
		bool	enableValidate{ false };
		
		std::vector<Vertex> vertices
		{};

		 std::vector<uint32_t> m_indices// can be uint16_t == 65535 unique vertices
		{};

		std::string_view TEXTURE_PATH = "../assets/textures/SpiderTex.jpg";
		std::string_view MODEL_PATH = "../assets/models/spider.obj";


		//to be removed
		TDSCamera camera{ -90.0f ,0.f};
		bool vsync{ false };
	};








}//namespace TDS



#endif//!VULKAN_CREATE_INSTANCE