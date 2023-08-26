
#version 450
layout(location = 0) in vec3 i_pos;
layout(location = 1) in vec3 i_norm;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat3 normalMatrix;

out vec3 fragPosition;
out vec3 fragNormal;

void main()
{
  fragNormal = normalMatrix * i_norm;

  vec4 worldPosition = modelMatrix * vec4(i_pos, 1.0);
  fragPosition = vec3(worldPosition);
  gl_Position = modelViewProjectionMatrix * vec4(i_pos, 1.0);
}