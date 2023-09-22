#include "first_app.hpp"

#include <stdexcept>

namespace tve {

  FirstApp::FirstApp() {
    createPipelineLayout();
    createPipeline();
    createCommandBuffers();
  }

  FirstApp::~FirstApp() {
    vkDestroyPipelineLayout(tveDevice.device(), pipelineLayout, nullptr);
  }

  void FirstApp::run() {
    while (!tveWindow.shouldClose()) {
      glfwPollEvents();
    }
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
    auto pipelineConfig = TvePipeline::defaultPipelineConfigInfo(tveSwapChain.width(), tveSwapChain.height());
    pipelineConfig.renderPass = tveSwapChain.getRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    tvePipeline = std::make_unique<TvePipeline>(tveDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
  }

  void FirstApp::createCommandBuffers() {}
  void FirstApp::drawFrame() {}
}
