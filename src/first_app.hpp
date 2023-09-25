#pragma once

#include "tve_window.hpp"
#include "tve_pipeline.hpp"
#include "tve_device.hpp"
#include "tve_swap_chain.hpp"
#include "tve_model.hpp"

#include <memory>
#include <vector>

namespace tve {

  class FirstApp {

  public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    FirstApp();
    ~FirstApp();


    FirstApp(const FirstApp &) = delete;
    FirstApp &operator=(const FirstApp &) = delete;

    void run();

  private:
    void loadModels();
    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();
    void drawFrame();
    void recreateSwapChain();
    void recordCommandBuffer(int imageIndex);

    TveWindow tveWindow{WIDTH, HEIGHT, "Hello, Vulkan!"};
    TveDevice tveDevice{tveWindow};
    std::unique_ptr<TveSwapChain> tveSwapChain;
    std::unique_ptr<TvePipeline> tvePipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;
    std::unique_ptr<TveModel> tveModel;
  };
}

