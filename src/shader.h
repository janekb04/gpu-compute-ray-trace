#ifndef SHADER_H
#define SHADER_H

#include "extern.h"
#include "fwd_decl.h"
#include "log.h"
#include <string_view>

class Shader {
  GLuint name;
  friend class ShaderProgram;

public:
  Shader(GLenum shader_type, const std::string_view source)
      : name{glCreateShader(shader_type)} {
    {
      const GLchar *const source_string = source.data();
      const GLint source_size = source.size();
      glShaderSource(name, 1, &source_string, &source_size);
    }
    glCompileShader(name);
    check_compilation_status();
  }
  ~Shader() { glDeleteShader(name); }

private:
  void check_compilation_status() const {
    int success;
    constexpr size_t INFO_LOG_SZ = 512;
    char info_log[INFO_LOG_SZ];
    glGetShaderiv(name, GL_COMPILE_STATUS, &success);

    if (!success) {
      glGetShaderInfoLog(name, INFO_LOG_SZ, nullptr, info_log);
      LOG_WARNING(info_log);
    }
  }
};

#endif