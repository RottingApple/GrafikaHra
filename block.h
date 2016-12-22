//
// Created by peter on 09.12.2016.
//

#ifndef PPGSO_BLOCK_H
#define PPGSO_BLOCK_H

#include <mesh.h>
#include <texture.h>
#include <shader.h>
#include "object.h"

class Block : public Object {
public:
    Block();
    ~Block();

    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

private:

    // Static resources (Shared between instances)
    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};
typedef std::shared_ptr< Block > BlockPtr;

#endif //PPGSO_BLOCK_H
