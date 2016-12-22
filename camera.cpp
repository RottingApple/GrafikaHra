#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"

#define PI 3.14159265358979323846f

Camera::Camera(float fow, float ratio, float near, float far) {
  float fowInRad = (PI/180.0f) * fow;
    updateCamera = false;
    time = 0;
  projectionMatrix = glm::perspective(fowInRad, ratio, near, far);
  up = glm::vec3(0,1,0);
  position = glm::vec3(0,0,0);
  back = glm::vec3(0,0,-1);
}

Camera::~Camera() {
}

void Camera::Update(float dt) {
//  GLfloat radius = 10.0f;
//  GLfloat camX = sin(glfwGetTime()) * radius;
//  GLfloat camZ = cos(glfwGetTime()) * radius;
//  position.x = camX;
//  position.z = camZ;
    if(updateCamera){
        time +=dt;
        if(time < 0.75f)
            position.x += 0.03f;
        else if(time < 1.5f)
            position.x -= 0.03f;
        else{
            updateCamera = false;
            time = 0;
            position.x = tempx;
        }
    }else
        tempx = position.x;
    viewMatrix = glm::lookAt(position, glm::vec3(0.0,0.0,0.0), up);
}
