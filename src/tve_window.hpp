#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

namespace tve {

  class TveWindow {

  public:
    TveWindow(int w, int h, std::string name);
    ~TveWindow();

    TveWindow(const TveWindow &) = delete;
    TveWindow &operator=(const TveWindow &) = delete;

    bool shouldClose() { return glfwWindowShouldClose(window); }
    VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }
    bool wasWindowResized() { return framebufferResized; }
    void resetWindowResizedFlag() { framebufferResized = false; }

    void createWindowSurface(VkInstance instance, VkSurfaceKHR *surface);

  private:
    void initWindow();
    static void framebufferResizeCallback(GLFWwindow *window, int width, int height);

    int width;
    int height;
    bool framebufferResized = false;

    std::string windowName;
    GLFWwindow *window;

  };
}
