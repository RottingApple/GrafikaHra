#ifndef PPGSO_PLAYER_H
#define PPGSO_PLAYER_H

#include <texture.h>
#include <shader.h>
#include <mesh.h>
#include "object.h"
#include "player_platform.h"
#include "player_head.h"

class Player : public Object {
public:
  Player();
  ~Player();
  PlatformPtr playerPlatform;
    HeadPtr playerHead;
  bool Update(Scene &scene, float dt) override;
  void Render(Scene &scene) override;

private:

  static MeshPtr mesh;
  static ShaderPtr shader;
  static TexturePtr texture;
};
typedef std::shared_ptr< Player > PlayerPtr;
#endif //PPGSO_PLAYER_H
