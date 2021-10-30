#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "extern.h"
#include "log.h"
#include "shader.h"

class ShaderProgram {
  GLuint name;

public:
  ShaderProgram(auto &&...shaders) : name{glCreateProgram()} {
    ((glAttachShader(name, shaders.name)), ...);
    glLinkProgram(name);
    check_link_status();
  }
  ~ShaderProgram() { glDeleteProgram(name); }

private:
  void check_link_status() const {
    int success;
    constexpr size_t INFO_LOG_SZ = 512;
    char info_log[INFO_LOG_SZ];
    glGetProgramiv(name, GL_LINK_STATUS, &success);

    if (!success) {
      glGetProgramInfoLog(name, INFO_LOG_SZ, nullptr, info_log);
      LOG_WARNING(info_log);
    }
  }
};

#endif