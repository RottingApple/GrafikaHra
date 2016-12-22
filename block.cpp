//
// Created by peter on 09.12.2016.
//
#include "block.h"
#include <gl_object_vert.h>
#include <gl_object_frag.h>
#include <GLFW/glfw3.h>
#include "player.h"
#include "scene.h"
#define PI 3.14159265358979323846f
Block::Block() {

    scale *= 1.5f;
    rotation.x -= PI/6;
    if (!shader) shader = ShaderPtr(new Shader{gl_object_vert, gl_object_frag});
    if (!texture) texture = TexturePtr(new Texture{"ruby_texture.rgb", 512,512});
    if (!mesh) mesh = MeshPtr(new Mesh{shader, "diamond.obj"});
}

Block::~Block() {
}

bool Block::Update(Scene &scene, float dt) {
    GenerateModelMatrix();
    return true;
}

void Block::Render(Scene &scene) {
    shader->Use();

    // use camera
    shader->SetMatrix(scene.camera->projectionMatrix, "ProjectionMatrix");
    shader->SetMatrix(scene.camera->viewMatrix, "ViewMatrix");

    // render mesh
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
MeshPtr Block::mesh;
ShaderPtr Block::shader;
TexturePtr Block::texture;