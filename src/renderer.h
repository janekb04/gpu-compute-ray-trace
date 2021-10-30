#include <GL/glew.h>

class Renderer {
  GLuint compute_program;

public:
  Renderer() {
    compute_program = create_compute_program();
    // do not format
    // this
    // code
  }
  void draw() {
    {
      const float clear_color[]{1, 1, 1, 0};
      glClearNamedFramebufferfv(0, GL_COLOR, 0, clear_color);
    }
  }

private:
  GLuint create_compute_program() {
    const char *const shader_source = "";
    GLuint compute_shader = glCreateShader(GL_COMPUTE_SHADER);
    glShaderSource(compute_shader, 1, &shader_source, nullptr);
    glCompileShader(compute_shader);
    check_shader_compilation_status(compute_shader);

    GLuint compute_program = glCreateProgram();
    glAttachShader(compute_program, compute_shader);
    glLinkProgram(compute_program);
    check_program_link_status(compute_program);

    glDeleteShader(compute_shader);

    return compute_program;
  }
  void check_shader_compilation_status(GLuint shader) {
    int success;
    constexpr size_t INFO_LOG_SZ = 512;
    char info_log[INFO_LOG_SZ];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(shader, INFO_LOG_SZ, nullptr, info_log);
      LOG_WARNING(info_log);
    }
  }
  void check_program_link_status(GLuint program) {
    int success;
    constexpr size_t INFO_LOG_SZ = 512;
    char info_log[INFO_LOG_SZ];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
      glGetProgramInfoLog(program, INFO_LOG_SZ, nullptr, info_log);
      LOG_WARNING(info_log);
    }
  }
};