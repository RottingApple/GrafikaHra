#include "space.h"
#include "scene.h"
#include "gl_space_frag.h"
#include "gl_space_vert.h"

Space::Space() {
  // Z of 1 means back as there is no perspective projection applied during render
  position.z = 1;
  // Initialize static resources if needed
  if (!shader) shader = ShaderPtr(new Shader{gl_space_vert, gl_space_frag});
  if (!texture) texture = TexturePtr(new Texture{"pozadie_hry.rgb",  512,512});
  if (!mesh) mesh = MeshPtr(new Mesh{shader, "quad.obj"});
}

Space::~Space() {
}

bool Space::Update(Scene &scene, float dt) {

  GenerateModelMatrix();
  return true;
}

void Space::Render(Scene &scene) {
  shader->Use();
  shader->SetMatrix(modelMatrix, "ModelMatrix");
  shader->SetTexture(texture, "Texture");
  mesh->Render();
}

// Static resources
MeshPtr Space::mesh;
ShaderPtr Space::shader;
TexturePtr Space::texture;
