#ifndef RENDERER_H
#define RENDERER_H

#include "extern.h"
#include "shader.h"
#include "shader_program.h"
#include "utility.h"

class Renderer {
  ShaderProgram compute_program;
  ShaderProgram fullscreen_quad_program;
  GLuint dummy_VAO;

public:
  Renderer()
      : compute_program{Shader{GL_COMPUTE_SHADER, read_file("main.comp")}},
        fullscreen_quad_program{
            Shader{GL_VERTEX_SHADER, read_file("quad.vert")},
            Shader{GL_FRAGMENT_SHADER, read_file("quad.frag")}} {
    glCreateVertexArrays(1, &dummy_VAO);
  }
  void draw() {
    {
      const float clear_color[]{0, 1, 1, 1};
      glClearNamedFramebufferfv(0, GL_COLOR, 0, clear_color);

      fullscreen_quad_program.use();
      glBindVertexArray(dummy_VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);
    }
  }
};

#endif