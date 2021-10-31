#version 460 core

vec2 positions[3] = vec2[3](vec2(-1, -3), vec2(3, 1), vec2(-1, 1));

out vec2 uv;

void main() {
  uv = positions[gl_VertexID];
  gl_Position = vec4(positions[gl_VertexID], 0, 1);
}