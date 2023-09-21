#pragma once

#include "tve_window.hpp"
#include "tve_pipeline.hpp"
#include "tve_device.hpp"

namespace tve {

  class FirstApp {

  public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();

  private:
    TveWindow tveWindow{WIDTH, HEIGHT, "Hello, Vulkan!"};
    TveDevice tveDevice{tveWindow};
    TvePipeline tvePipeline{tveDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", TvePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
  };
}

