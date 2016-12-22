#version 150
// The inputs will be fed by the vertex buffer objects
in vec3 Position;
in vec2 TexCoord;
in vec3 Normal;

// This will be passed to the fragment shader
out vec2 fragTexCoord;

// Normal to pass to the fragment shader
out vec3 fragNormal;
out vec3 fragVert;
// Matrices as program attributes
uniform mat4 ProjectionMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ModelMatrix;

void main() {
  // Copy the input to the fragment shader
  fragTexCoord = TexCoord;
  fragVert = Position;
  fragNormal = Normal;
  // Normal in world coordinates

  // Calculate the final position on screen
  gl_Position =  ProjectionMatrix * ViewMatrix * ModelMatrix * vec4(Position, 1.0);
}
