//
// Created by peter on 10.12.2016.
//

#ifndef PPGSO_PLAYER_HEAD_H
#define PPGSO_PLAYER_HEAD_H


#include <texture.h>
#include <mesh.h>
#include "object.h"

class Player_Head : public Object {
public:
    Player_Head();
    ~Player_Head();
    bool Update(Scene &scene, float dt) override;
    bool Update(Scene &scene, float dt, glm::mat4 playermatrix);
    void Render(Scene &scene) override;

private:
    glm::vec3 rotMomentum;
    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;
};
typedef std::shared_ptr< Player_Head > HeadPtr;



#endif //PPGSO_PLAYER_HEAD_H
