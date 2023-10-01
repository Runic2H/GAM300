// Application.cpp
#include <shlwapi.h>                // GetModuleFileNameA(), PathRemoveFileSpecA()
#pragma comment(lib, "shlwapi.lib") // Needed for <shlwapi.h>
#include <vector>
#include <array>
#include <sstream>

#include "EditorApp.h"
#include "Logger/Logger.h"
#include "Input/Input.h"
#include "vulkanTools/Model.h"
#include "imguiHelper/ImguiHelper.h"
#include "vulkanTools/FrameInfo.h"

#include "sceneManager/sceneManager.h"

#include <imgui/imgui.h>

bool isPlaying = false;

namespace TDS
{
    Application::Application(HINSTANCE hinstance, int& nCmdShow, const wchar_t* classname, WNDPROC wndproc)
        :m_window(hinstance, nCmdShow, classname)
    {
        m_window.createWindow(wndproc, 1280, 800);
        m_pVKInst = std::make_shared<VulkanInstance>(m_window);
        m_Renderer = std::make_shared<Renderer>(m_window, *m_pVKInst.get());
        Log::Init();
        TDS_INFO("window width: {}, window height: {}", m_window.getWidth(), m_window.getHeight());

        m_globalPool = DescriptorPool::Builder(*m_pVKInst.get()).setMaxSets(VulkanSwapChain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VulkanSwapChain::MAX_FRAMES_IN_FLIGHT)
            .addPoolSize(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VulkanSwapChain::MAX_FRAMES_IN_FLIGHT)
            .build();

        models = Model::createModelFromFile(*m_pVKInst.get(), "Test.bin");
    }
    void  Application::handleMessages(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        IMGUI_WIN32_WNDPROCHANDLER_FORWARD_DECLARATION;
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam); //for imgui implementation
        //can extern  some imgui wndproc handler | tbc

        switch (uMsg)
        {

        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        case WM_PAINT:
            ValidateRect(m_window.getWindowHandler(), NULL);
            break;
        case WM_SIZE: //for resize of window may need it for fullscreen?
            m_window.setWidth(LOWORD(lParam));
            m_window.setHeight(HIWORD(lParam));
            m_window.WindowIsResizing(true);
            break;
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
        {
            Input::processMouseInput(wParam, lParam);
        }break;

        case WM_MOUSEMOVE:
        {
            Input::updateMousePosition(lParam);
        }break;

        case WM_MOUSEWHEEL:
        {
            Input::processMouseScroll(wParam);
        }break;

        case WM_SYSKEYDOWN:
        case WM_SYSKEYUP:
        case WM_KEYDOWN:
        {
            uint32_t VKcode = static_cast<uint32_t>(wParam);
            WORD keyflags = HIWORD(lParam);
            if (!(keyflags & KF_REPEAT))
            {
                Input::keystatus = Input::KeyStatus::PRESSED;
            }
            else if (keyflags & KF_REPEAT)
                Input::keystatus = Input::KeyStatus::REPEATED;

            bool wasDown = (lParam & (1 << 30)) != 0;
            bool isDown = (static_cast<unsigned int>(lParam) & (1 << 31)) == 0;
            Input::processKeyboardInput(VKcode, wasDown, isDown);
        }break;
        case WM_KEYUP:
        {
            uint32_t VKcode = static_cast<uint32_t>(wParam);
            bool wasDown = (lParam & (1 << 30)) != 0;
            bool isDown = (static_cast<unsigned int>(lParam) & (1 << 31)) == 0;

            Input::processKeyboardInput(VKcode, wasDown, isDown);
            Input::keystatus = Input::KeyStatus::RELEASED;
            Input::keystatus = Input::KeyStatus::IDLE;
        }break;
        }
    }
    void Application::Initialize()
    {
        m_AssetManager.Init();
        m_AssetManager.PreloadAssets();
        SceneManager::GetInstance()->Init();
        ecs.initializeSystems(1);
    }

    void Application::Update()
    {

        std::vector<std::unique_ptr<Buffer>> uboBuffers(VulkanSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < uboBuffers.size(); i++) {
            uboBuffers[i] = std::make_unique<Buffer>(
                *m_pVKInst.get(),
                sizeof(GlobalUBO),
                1,
                VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
                VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
            uboBuffers[i]->map();
        }

        auto globalSetLayout =
            DescriptorSetLayout::Builder(*m_pVKInst.get())
            .AddBinding(0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, VK_SHADER_STAGE_ALL_GRAPHICS)
            //.AddBinding(0,VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, VK_SHADER_STAGE_ALL_GRAPHICS)
            .build();

        std::vector<VkDescriptorSet> globalDescriptorSets(VulkanSwapChain::MAX_FRAMES_IN_FLIGHT);
        for (int i = 0; i < globalDescriptorSets.size(); i++) {
            auto bufferInfo = uboBuffers[i]->descriptorinfo();
            DescriptorWriter(*globalSetLayout, *m_globalPool)
                .writeBuffer(0, &bufferInfo)
                .Build(globalDescriptorSets[i]);
        }



        RendererManager renderermgr{ *m_pVKInst.get(), m_Renderer->getSwapChainRenderPass(), globalSetLayout->getDescSetLayout() };
        //PointLightSystem PlightSystem{ *m_pVKInst.get(), m_Renderer->getSwapChainRenderPass(), globalSetLayout->getDescSetLayout() };
        initImgui();
        float lightx = 0.f;
        while (m_window.processInputEvent())
        {
            float DeltaTime;
            {
                auto  Now = std::chrono::high_resolution_clock::now();
                std::chrono::duration<float> ElapsedSeconds = Now - Clock;
                DeltaTime = ElapsedSeconds.count();
                Clock = Now;
            }

            if (isPlaying)
            {
                ecs.runSystems(1, DeltaTime);
            }

            imguiHelper::Update();
            //ImGui::Begin("Profiler");
            //ImGui::Text("FPS: %.3f", 1.f / DeltaTime);
            //ImGui::End();

            if (auto commandbuffer = m_Renderer->BeginFrame())
            {
                int frameIndex = m_Renderer->getFrameIndex();

                FrameInfo frameinfo{
                    frameIndex,
                    DeltaTime,
                    commandbuffer,
                    m_camera,
                    globalDescriptorSets[frameIndex],
                    *models.get()
                };

                m_camera.UpdateCamera(DeltaTime);
                /*UniformBufferObject ubo{};
                ubo.model = Mat4();
                ubo.view = m_camera.GetViewMatrix();
                ubo.proj = Mat4::Perspective(m_camera.m_Fov * Mathf::Deg2Rad,
                    m_Renderer->getAspectRatio(), 0.1f, 10.f);
                ubo.proj.m[1][1] *= -1;*/

                lightx = lightx < -1.f ? 1.f : lightx - 0.005f;

                GlobalUBO PLUbo;
                PLUbo.m_Projection = Mat4::Perspective(m_camera.m_Fov * Mathf::Deg2Rad,
                    m_Renderer->getAspectRatio(), 0.1f, 10.f);
                PLUbo.m_Projection.m[1][1] *= -1;
                PLUbo.m_View = m_camera.GetViewMatrix();
                PLUbo.m_vPointLights[0].m_Position = Vec4(lightx, 0.5f, 0.f, 0.2f);
                PLUbo.m_vPointLights[0].m_Color = Vec4(1.f, 1.f, 1.f, 1.f);
                //PlightSystem.update(frameinfo, PLUbo);
                uboBuffers[frameIndex]->WritetoBuffer(&PLUbo);
                uboBuffers[frameIndex]->flush();

                m_Renderer->BeginSwapChainRenderPass(commandbuffer);

                renderermgr.draw(frameinfo);
                //ImGui::ShowDemoWindow();
                // for (uint32_t i = 0; i < m_Renderer->getImageViewContainer().size(); i++)
                //     m_Dset[i] = ImGui_ImplVulkan_AddTexture(VK_NULL_HANDLE, m_Renderer->getImageView(i), VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
               /*  ImGui::Begin("Scene");
                 ImGui::Image((ImTextureID)globalDescriptorSets[frameIndex], {1, 0}, {0, 1});
                 ImGui::End();*/
                imguiHelper::Draw(commandbuffer);

                m_Renderer->EndSwapChainRenderPass(commandbuffer);
                m_Renderer->EndFrame();
            }

            //// Update and Render additional Platform Windows
            //if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            //{
            //    ImGui::UpdatePlatformWindows();
            //    ImGui::RenderPlatformWindowsDefault();
            //}
            Input::scrollStop();
        }
        vkDeviceWaitIdle(m_pVKInst.get()->getVkLogicalDevice());
        imguiHelper::Exit();
        ecs.destroy();
    }

    Application::~Application()
    {
        m_window.~WindowsWin();
    }

    bool Application::initImgui()
    {
        /* VkDescriptorPoolSize pool_sizes[] =
         {
             { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
             { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
             { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
             { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
             { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
             { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
             { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
             { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
             { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
             { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
             { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
         };

         VkDescriptorPoolCreateInfo pool_info = {};
         pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
         pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
         pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
         pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
         pool_info.pPoolSizes = pool_sizes;

         vkCreateDescriptorPool(m_pVKInst.get()->m_logicalDevice, &pool_info, nullptr
           , &m_pVKInst.get()->m_ImguiDescriptorPool);*/

        ImGui_ImplVulkan_InitInfo initInfo{};

        initInfo.Instance = m_pVKInst->getInstance();
        initInfo.PhysicalDevice = m_pVKInst->getVkPhysicalDevice();
        initInfo.Device = m_pVKInst->getVkLogicalDevice();
        initInfo.QueueFamily = m_pVKInst->findPhysicalQueueFamilies().graphicsFamily.value();
        initInfo.Queue = m_pVKInst->getGraphicsQueue();
        initInfo.PipelineCache = VK_NULL_HANDLE;


        initInfo.DescriptorPool = m_globalPool.get()->getDescPool();
        initInfo.Subpass = 0;
        initInfo.MinImageCount = 2;
        initInfo.ImageCount = 2;
        initInfo.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        initInfo.Allocator = nullptr;
        initInfo.CheckVkResultFn = nullptr;

        imguiHelper::InitializeImgui(initInfo, m_Renderer->getSwapChainRenderPass(), m_window.getWindowHandler());

        if (VkCommandBuffer FCB{ m_pVKInst->beginSingleTimeCommands() }; FCB != nullptr)
        {
            imguiHelper::ImguiCreateFont(FCB);
            m_pVKInst->endSingleTimeCommands(FCB);
            ImGui_ImplVulkan_DestroyFontUploadObjects();
        }
        else
        {
            std::cerr << "failed to create command buffer for imgui font creation\n";
            return false;
        }

        /* for(uint32_t i = 0; i < m_pVKInst.get()->swapChainImageViews.size(); i++)
             m_pVKInst.get()->m_descriptorSets[i] = ImGui_ImplVulkan_AddTexture(m_pVKInst.get()->m_textureSampler, m_pVKInst.get()->swapChainImageViews[i], VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);*/


        return true;

    }

}// end TDS