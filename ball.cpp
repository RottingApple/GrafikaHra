//
// Created by peter on 05.12.2016.
//
#include <shader.h>
#include "scene.h"
#include <gl_object_frag.h>
#include "ball.h"
#include "player.h"
#include "block.h"
#include "generator.h"
#include <gl_object_vert.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define Map_Edges 7.6f

Ball::Ball(){
    if (!shader) shader = ShaderPtr(new Shader{gl_object_vert,gl_object_frag});
    if (!texture) texture = TexturePtr(new Texture{"lopticka.rgb", 512,512});
    if (!mesh) mesh = MeshPtr(new Mesh{shader, "sphere.obj"});
    northleft = false;
    northright = true;
    southleft = false;
    southright = false;
    scale *= 0.75f;
    speed = 0.025f;
    edge = 0.3f;
    time = 0;
}
Ball::~Ball(){
}

bool Ball::Update(Scene &scene, float dt){
    time+= dt;
    if(time > 60){
        time = 0;
        speed += 0.005f;
    }
    UpdateDirection(scene);
    Move();
    GLfloat radius = 5.0f;
    GLfloat camX = sin(glfwGetTime())* radius;
    GLfloat camZ = cos(glfwGetTime())* radius;
    rotation.x = camX;
    rotation.y = camZ;
    GenerateModelMatrix();
    if(position.y < 20 && position.y > -10)
    return true;
    else
        return false;
}

void Ball::Render(Scene &scene){
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

void Ball::UpdateDirection(Scene &scene){

    if(position.x > Map_Edges || position.x < - Map_Edges ) { // bocne steny
        if (northright){
            northright = false;
            northleft = true;
        }else if(northleft){
            northleft = false;
            northright = true;
        }else if(southleft){
            southleft = false;
            southright = true;
        }else{
            southright = false;
            southleft = true;
        }
    }else if(position.y > Map_Edges ){ // horna stena
        if (northright){
            northright = false;
            southleft = true;
        }else{
            northleft = false;
            southright = true;
        }
        edge = Rand(0.2f,0.5f);
    }

    for(auto object : scene.objects){
        if (object.get() == this) continue;
            auto player = std::dynamic_pointer_cast<Player>(object);
             auto block = std::dynamic_pointer_cast<Block>(object);

        if (!player && !block) continue;

        if(player)
            CheckPlayer(player);
        else
        if(glm::distance(position, object->position) < (object->scale.y + scale.y)*0.5f) {
            if(block){
                scene.isalive = false;
                scene.objects.remove(block);
                scene.camera->updateCamera = true;
                if (northright){
                    northright = false;
                    southright = true;
                }else if(northleft){
                    northleft = false;
                    southleft = true;
                }else if(southleft){
                    southleft = false;
                    northleft = true;
                }else{
                    southright = false;
                    northright = true;
                }
            }
            edge = Rand(0.2f,0.5f);
        }
    }
}
void Ball::Move(){
    if(northright){
        position.x -= speed;
        position.y += speed * edge;
    }else if(northleft){
        position.x += speed;
        position.y += speed * edge;
    }else if(southleft){
        position.x -= speed;
        position.y -= speed * edge;
    } else{
        position.x += speed;
        position.y -= speed * edge;
    }
}
void Ball::CheckPlayer(PlayerPtr player){
    PlatformPtr playerPlatform = player->playerPlatform;
    HeadPtr playerHead = player->playerHead;
    if(glm::distance(position, playerPlatform->position) < (playerPlatform->scale.y + scale.y)*0.5f) {
        if(southleft){
            southleft = false;
            northleft = true;
        }else if(southright){
            southright = false;
            northright = true;
        }
    }
    glm::vec3 finalposition = playerPlatform->position + playerHead->position;
    if(glm::distance(position, finalposition) < (playerHead->scale.y + scale.y)*0.5f) {
        if(southleft){
            southleft = false;
            northright = true;
        }else if(southright){
            southright = false;
            northleft = true;
        }
    }
}
// shared resources
MeshPtr Ball::mesh;
ShaderPtr Ball::shader;
TexturePtr Ball::texture;