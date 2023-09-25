#include "first_app.hpp"

#include <stdexcept>
#include <array>
#include <cassert>

namespace tve {

  FirstApp::FirstApp() {
    loadModels();
    createPipelineLayout();
    recreateSwapChain();
    createCommandBuffers();
  }

  FirstApp::~FirstApp() {
    vkDestroyPipelineLayout(tveDevice.device(), pipelineLayout, nullptr);
  }

  void FirstApp::run() {
    while (!tveWindow.shouldClose()) {
      glfwPollEvents();
      drawFrame();
    }

    vkDeviceWaitIdle(tveDevice.device());
  }

  void FirstApp::loadModels() {
    std::vector<TveModel::Vertex> vertices {
      {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
      {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
      {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };

    tveModel = std::make_unique<TveModel>(tveDevice, vertices);
  }

  void FirstApp::createPipelineLayout() {
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;
    if (vkCreatePipelineLayout(tveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
      throw std::runtime_error("failed to create pipeline layout");
    }
  }

  void FirstApp::createPipeline() {
    auto pipelineConfig = TvePipeline::defaultPipelineConfigInfo(tveSwapChain->width(), tveSwapChain->height());
    pipelineConfig.renderPass = tveSwapChain->getRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    tvePipeline = std::make_unique<TvePipeline>(tveDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
  }

  void FirstApp::createCommandBuffers() {
    commandBuffers.resize(tveSwapChain->imageCount());

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandPool = tveDevice.getCommandPool();
    allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

    if (vkAllocateCommandBuffers(tveDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
      throw std::runtime_error("failed to allocate command buffers");
    }
  }

  void FirstApp::recordCommandBuffer(int imageIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS) {
      throw std::runtime_error("failed to begin recording command buffer");
    }

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = tveSwapChain->getRenderPass();
    renderPassInfo.framebuffer = tveSwapChain->getFrameBuffer(imageIndex);

    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = tveSwapChain->getSwapChainExtent();

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    tvePipeline->bind (commandBuffers[imageIndex]);
    tveModel->bind(commandBuffers[imageIndex]);
    tveModel->draw(commandBuffers[imageIndex]);

    vkCmdEndRenderPass(commandBuffers[imageIndex]);
    if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS) {
      std::runtime_error("failed to record command buffer");
    }
  }

  void FirstApp::recreateSwapChain() {
    auto extent = tveWindow.getExtent();
    while (extent.width == 0 || extent.height == 0) {
      extent = tveWindow.getExtent();
      glfwWaitEvents();
    }

    vkDeviceWaitIdle(tveDevice.device());
    tveSwapChain = std::make_unique<TveSwapChain>(tveDevice, extent);
    createPipeline();
  }

  void FirstApp::drawFrame() {
    uint32_t imageIndex;
    auto result = tveSwapChain->acquireNextImage(&imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
      recreateSwapChain();
      return;
    }

    if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
      throw std::runtime_error("failed to acquire swap chain image");
    }

    recordCommandBuffer(imageIndex);
    result = tveSwapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
    if (result ==VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || tveWindow.wasWindowResized()) {
      tveWindow.resetWindowResizedFlag();
      recreateSwapChain();
      return;
    }

    if (result != VK_SUCCESS) {
      throw std::runtime_error("failed to present swap chain image");
    }

  }
}
