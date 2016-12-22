//
// Created by peter on 10.12.2016.
//

#ifndef PPGSO_PLAYER_PLATFORM_H
#define PPGSO_PLAYER_PLATFORM_H

#include <texture.h>
#include <mesh.h>
#include "object.h"

class Player_Platform : public Object {
public:
    Player_Platform();
    ~Player_Platform();
    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

private:

    // Static resources (Shared between instances)
    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};
typedef std::shared_ptr< Player_Platform > PlatformPtr;


#endif //PPGSO_PLAYER_PLATFORM_H
