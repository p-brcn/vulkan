#pragma once

#include "tve_model.hpp"

#include <memory>

namespace tve {
  class TveGameObject {

  public:
    using id_t = unsigned int;

    static TveGameObject createGameObject() {
      static id_t currentId = 0;
      return TveGameObject{currentId++};
    }

    TveGameObject(const TveGameObject &) = delete;
    TveGameObject &operator=(const TveGameObject &) = delete;
    TveGameObject(TveGameObject&&) = default;
    TveGameObject &operator(TveGameObject&&) = default;

    id_t getId() { return id; };

    std::shared_ptr<TveModel> model{};
    glm::vec3 color{};

  private:
    TveGameObject(id_t objId) : id{objId} {}
    id_t id;
  };
}
