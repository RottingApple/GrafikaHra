//
// Created by peter on 05.12.2016.
//

#ifndef PPGSO_BALL_H
#define PPGSO_BALL_H


#include <mesh.h>
#include "object.h"
#include "player.h"

class Ball : public Object{
public:
    Ball();
    ~Ball();
    bool Update(Scene &scene, float dt) override;
    void Render(Scene &scene) override;

private:
    bool northleft;
    bool northright;
    bool southleft;
    bool southright;
    float speed;
    float edge;
    float time;
    static MeshPtr mesh;
    static ShaderPtr shader;
    static TexturePtr texture;

    void UpdateDirection(Scene &scene);

    void Move();

    void CheckPlayer(PlayerPtr player);
};
typedef std::shared_ptr<Ball> BallPtr;

#endif //PPGSO_BALL_H
