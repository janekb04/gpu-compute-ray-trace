#ifndef RENDERER_H
#define RENDERER_H

#include "extern.h"
#include "shader.h"
#include "shader_program.h"
#include "utility.h"

class Renderer {
  ShaderProgram compute_program;

public:
  Renderer()
      : compute_program{Shader{GL_COMPUTE_SHADER, read_file("main.comp")}} {}
  void draw() {
    {
      const float clear_color[]{1, 1, 1, 0};
      glClearNamedFramebufferfv(0, GL_COLOR, 0, clear_color);
    }
  }
};

#endif