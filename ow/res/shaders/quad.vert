#version 450
layout(location = 0) in vec3 i_pos;
layout(location = 1) in vec3 i_norm;
layout(location = 2) in vec2 i_tex;


out vec3 fragPosition;
out vec3 fragNormal;
out vec2 fragTex;

void main()
{
  fragTex = i_tex;
  gl_Position =  vec4(i_pos, 1.0);
}