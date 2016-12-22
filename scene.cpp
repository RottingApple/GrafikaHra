#include "scene.h"
#include "generator.h"

Scene::Scene() {

    light.position=glm::vec3(0.0f, -10.0f, -5.0f);
    light.position2=glm::vec3(0.0f, +10.0f, -5.0f);
    light.intensities=glm::vec3(0.5f, 0.5f, 0.5f);
    light.ambientCoefficient = 0.04f;
    light.attenuation = 0.2f;
}

Scene::~Scene() {
}

void Scene::Update(float time) {
  camera->Update(time);

  // Use iterator to update all objects so we can remove while iterating
  auto i = std::begin(objects);

  while (i != std::end(objects)) {
    // Update and remove from list if needed
      auto obj = i->get();
    if (!obj->Update(*this, time))
      i = objects.erase(i); // NOTE: no need to call destructors as we store shared pointers in the scene
    else
      ++i;
  }
}

void Scene::Render() {
  // Simply render all objects
  for (auto obj : objects )
    obj->Render(*this);
}

