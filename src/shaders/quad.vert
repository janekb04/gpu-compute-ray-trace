#version 460 core

vec2 positions[3] =
    vec2[3](vec2(-0.5f, -0.5f), vec2(0.5f, -0.5f), vec2(0.0f, 0.5f));

void main() { gl_Position = vec4(positions[gl_VertexID], 0, 1); }