#include "first_app.hpp"

namespace tve {
  void FirstApp::run() {
    while (!tveWindow.shouldClose()) {
      glfwPollEvents();
    }
  }
}
