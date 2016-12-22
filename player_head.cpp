//
// Created by peter on 10.12.2016.
//

#include "Player_Head.h"
#include <gl_object_vert.h>
#include <gl_object_frag.h>
#include <GLFW/glfw3.h>
#include "scene.h"
#define Right_Edge -6.6f
#define Left_Edge  6.6f
Player_Head::Player_Head() {
    scale.x *= 0.6f;
    scale.y *= 0.8f;
    rotMomentum = glm::vec3(0,0,  PI/3);
    if (!shader) shader = ShaderPtr(new Shader{gl_object_vert, gl_object_frag});
    if (!texture) texture = TexturePtr(new Texture{"texturakovu.rgb", 512,512});
    if (!mesh) mesh = MeshPtr(new Mesh{shader, "hlavaplatformy.obj"});
}

Player_Head::~Player_Head() {
}

bool Player_Head::Update(Scene &scene, float dt) {
}

bool Player_Head::Update(Scene &scene,float dt,glm::mat4 playermatrix){

    rotation += rotMomentum * dt;
    GenerateModelMatrix();

    modelMatrix = playermatrix * modelMatrix;
    return true;
}

void Player_Head::Render(Scene &scene) {
    shader->Use();
    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");
    shader->SetMatrix(modelMatrix, "ModelMatrix");
    shader->SetTexture(texture, "materialTex");

    shader->SetMatrix(modelMatrix, "model");
    shader->SetVector(scene.camera->position, "cameraPosition");
    shader->SetFloat(materialShininess, "materialShininess");
    shader->SetVector(materialSpecularColor, "materialSpecularColor");
    shader->SetVector(scene.light.position, "Lposition");
    shader->SetVector(scene.light.position2, "Lposition2");
    shader->SetVector(scene.light.intensities, "Lintensities");
    shader->SetFloat(scene.light.attenuation, "Lintensities");
    shader->SetFloat(scene.light.ambientCoefficient, "LambientCoefficient");
    mesh->Render();
}

// shared resources
MeshPtr Player_Head::mesh;
ShaderPtr Player_Head::shader;
TexturePtr Player_Head::texture;