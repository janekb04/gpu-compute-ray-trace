#version 460 core

in vec2 uv;
out vec4 frag_color;

void main() {
  vec3 ray_dir = normalize(vec3(uv, 1));
  frag_color = vec4(ray_dir, 1);
}