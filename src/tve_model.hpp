#pragma once

#include "tve_device.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>

#include <vector>

namespace tve {

  class TveModel {

  public:

    struct Vertex {
      glm::vec2 position;
      glm::vec3 color;

      static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
      static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();
    };

    TveModel(TveDevice &device, const std::vector<Vertex> &vertices);
    ~TveModel();


    TveModel(const TveModel &) = delete;
    TveModel &operator=(const TveModel &) = delete;

    void bind(VkCommandBuffer commandBuffer);
    void draw(VkCommandBuffer commandBuffer);

  private:
    void createVertexBuffers(const std::vector<Vertex> &vertices);

    TveDevice& tveDevice;
    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;
    uint32_t vertexCount;
  };
}

