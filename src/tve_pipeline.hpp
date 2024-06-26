#pragma once

#include <string>

#include "tve_device.hpp"

namespace tve {

  struct PipelineConfigInfo{
    PipelineConfigInfo(const PipelineConfigInfo &) = delete;
    PipelineConfigInfo &operator=(const PipelineConfigInfo &) = delete;

    VkPipelineViewportStateCreateInfo viewportInfo;
    VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
    VkPipelineRasterizationStateCreateInfo rasterizationInfo;
    VkPipelineMultisampleStateCreateInfo multisampleInfo;
    VkPipelineColorBlendAttachmentState colorBlendAttachment;
    VkPipelineColorBlendStateCreateInfo colorBlendInfo;
    VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
    std::vector<VkDynamicState> dynamicStateEnables;
    VkPipelineDynamicStateCreateInfo dynamicStateInfo;
    VkPipelineLayout pipelineLayout = nullptr;
    VkRenderPass renderPass = nullptr;
    uint32_t subpass = 0;
  };

  class TvePipeline {

  public:
    TvePipeline(TveDevice &device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);

    ~TvePipeline();

    TvePipeline(const TvePipeline &) = delete;
    TvePipeline &operator=(const TvePipeline &) = delete;

    void bind(VkCommandBuffer commandBuffer);
    static void defaultPipelineConfigInfo(PipelineConfigInfo& configInfo);


  private:
    static std::vector<char> readFile(const std::string& filepath);

    void createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo& configInfo);

    void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

    TveDevice& tveDevice;
    VkPipeline graphicsPipeline;
    VkShaderModule vertShaderModule;
    VkShaderModule fragShaderModule;
  };
}
