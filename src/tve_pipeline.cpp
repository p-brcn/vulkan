#include "tve_pipeline.hpp"

#include <fstream>
#include <stdexcept>
#include <iostream>

namespace tve {

  TvePipeline::TvePipeline(TveDevice &device, const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo configInfo) : tveDevice{device} {
    createGraphicsPipeline(vertFilepath, fragFilepath, configInfo);
  };

  std::vector<char> TvePipeline::readFile(const std::string& filepath) {
    std::ifstream file{filepath, std::ios::ate | std::ios::binary};

    if (!file.is_open()) {
      throw std::runtime_error("failed to open filepath: " + filepath);
    }

    size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    file.close();
    return buffer;
  }

  void TvePipeline::createGraphicsPipeline(const std::string& vertFilepath, const std::string& fragFilepath, const PipelineConfigInfo configInfo) {
    auto vertCode = readFile(vertFilepath);
    auto fragCode = readFile(fragFilepath);

    std::cout << "Vertex Shader Code Size: " << vertCode.size() << '\n';
    std::cout << "Fragment Shader Code Size: " << fragCode.size() << '\n';
  }

  void TvePipeline::createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    if (vkCreateShaderModule(tveDevice.device(), &createInfo, nullptr, shaderModule) != VK_SUCCESS) {
      throw std::runtime_error("failed to create shader module");
    }
  }

  PipelineConfigInfo TvePipeline::defaultPipelineConfigInfo(uint32_t width, uint32_t height) {
    PipelineConfigInfo configInfo{};

    return configInfo;
  };
}
