#include "player.h"
#include "scene.h"
#include "gl_object_frag.h"
#include "gl_object_vert.h"
#include <GLFW/glfw3.h>

#define Right_Edge -6.6f
#define Left_Edge  6.6f


Player::Player() {

    auto playerPlatform = PlatformPtr(new Player_Platform{});
    auto playerHead = HeadPtr(new Player_Head{});
    this->playerPlatform = playerPlatform;
    this->playerHead = playerHead;
    playerHead->position.y = 0.6;
    playerPlatform->position.y = -7.5f;

}

Player::~Player() {
}

bool Player::Update(Scene &scene, float dt) {


    playerPlatform->Update(scene,dt);
    playerHead->Update(scene,dt,playerPlatform->modelMatrix);
    return true;
}

void Player::Render(Scene &scene) {

    playerPlatform->Render(scene);
    playerHead->Render(scene);
}

// shared resources
MeshPtr Player::mesh;
ShaderPtr Player::shader;
TexturePtr Player::texture;