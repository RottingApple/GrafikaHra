#include "generator.h"
#include "block.h"
//#include "asteroid.h"

bool Generator::Update(Scene &scene, float dt) {

  if(!scene.isalive ){
      time += dt;
      if(time > 2) {
        auto block = BlockPtr(new Block{});
        block->position.y = +5;
        block->position.x = Rand(-5,5);
        scene.objects.push_back(block);
        scene.isalive = true;
        time = 0;
      }
  }
  return true;
}

void Generator::Render(Scene &scene) {
}

Generator::~Generator() {
}

Generator::Generator() {
  time = 2;
}
