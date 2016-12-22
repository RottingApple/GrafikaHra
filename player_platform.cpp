//
// Created by peter on 10.12.2016.
//
#include "Player_platform.h"
#include <gl_object_vert.h>
#include <gl_object_frag.h>
#include <GLFW/glfw3.h>
#include "scene.h"
#define Right_Edge -6.6f
#define Left_Edge  6.6f


Player_Platform::Player_Platform() {
    scale *= 1.5f;
    if (!shader) shader = ShaderPtr(new Shader{gl_object_vert, gl_object_frag});
    if (!texture) texture = TexturePtr(new Texture{"box_texture.rgb", 512,512});
    if (!mesh) mesh = MeshPtr(new Mesh{shader, "hraczaciatok.obj"});
}

Player_Platform::~Player_Platform() {
}

bool Player_Platform::Update(Scene &scene, float dt) {

    if(scene.keyboard[GLFW_KEY_LEFT] && (position.x + 15 * dt) < Left_Edge) {
        position.x += 15 * dt;
        rotation.z = -PI/8.0f;
    } else if(scene.keyboard[GLFW_KEY_RIGHT] && (position.x - 15 *dt) > Right_Edge) {
        position.x -= 15 * dt;
        rotation.z = PI/8.0f;
    }else {
        rotation.z = 0;
        rotation.x = 0;
    }
    GenerateModelMatrix();
    return true;
}

void Player_Platform::Render(Scene &scene) {
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
MeshPtr Player_Platform::mesh;
ShaderPtr Player_Platform::shader;
TexturePtr Player_Platform::texture;