#include <GL/glew.h>
#include <glfwpp/glfwpp.h>
#include <iostream>

void APIENTRY opengl_error_callback(GLenum source, GLenum type, GLuint id,
                                    GLenum severity, GLsizei length,
                                    const GLchar *msg, const void *data) {
  char message[BUFSIZ];

  const char *_source;
  const char *_type;
  const char *_severity;

  switch (source) {
  case GL_DEBUG_SOURCE_API:
    _source = "API";
    break;

  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
    _source = "WINDOW_SYSTEM";
    break;

  case GL_DEBUG_SOURCE_SHADER_COMPILER:
    _source = "SHADER_COMPILER";
    break;

  case GL_DEBUG_SOURCE_THIRD_PARTY:
    _source = "THIRD_PARTY";
    break;

  case GL_DEBUG_SOURCE_APPLICATION:
    _source = "APPLICATION";
    break;

  case GL_DEBUG_SOURCE_OTHER:
    _source = "OTHER";
    break;

  default:
    _source = "UNKNOWN";
    break;
  }

  switch (type) {
  case GL_DEBUG_TYPE_ERROR:
    _type = "ERROR";
    break;

  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    _type = "DEPRECATED_BEHAVIOR";
    break;

  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    _type = "UDEFINED_BEHAVIOR";
    break;

  case GL_DEBUG_TYPE_PORTABILITY:
    _type = "PORTABILITY";
    break;

  case GL_DEBUG_TYPE_PERFORMANCE:
    _type = "PERFORMANCE";
    break;

  case GL_DEBUG_TYPE_OTHER:
    _type = "OTHER";
    break;

  case GL_DEBUG_TYPE_MARKER:
    _type = "MARKER";
    break;

  default:
    _type = "UNKNOWN";
    break;
  }

  switch (severity) {
  case GL_DEBUG_SEVERITY_HIGH:
    _severity = "HIGH";
    break;

  case GL_DEBUG_SEVERITY_MEDIUM:
    _severity = "MEDIUM";
    break;

  case GL_DEBUG_SEVERITY_LOW:
    _severity = "LOW";
    break;

  case GL_DEBUG_SEVERITY_NOTIFICATION:
    _severity = "NOTIFICATION";
    break;

  default:
    _severity = "UNKNOWN";
    break;
  }

  std::snprintf(message, BUFSIZ, "%s (%d) of %s severity, raised from %s: %s\n",
                _type, id, _severity, _source, msg);

  if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
    //__debugbreak();
    std::clog << message << '\n';
}

int main() {
  // init window
  auto GLFW = glfw::init();

  {
    glfw::WindowHints hints{};
    hints.contextVersionMajor = 4;
    hints.contextVersionMinor = 6;
    hints.openglProfile = glfw::OpenGlProfile::Core;
    hints.transparentFramebuffer = true;
    hints.resizable = false;
    hints.apply();
  }

  const int WND_WIDTH = 640, WND_HEIGHT = 480;
  glfw::Window window{WND_WIDTH, 480, "GPU compute ray trace"};
  glfw::makeContextCurrent(window);

  if (glewInit() != GLEW_OK) {
    throw std::runtime_error("Could not initialize GLEW");
  }

  glDebugMessageCallback(opengl_error_callback, NULL);

  while (!window.shouldClose()) {
    {
      const float clear_color[]{1, 1, 1, 0};
      glClearNamedFramebufferfv(0, GL_COLOR, 0, clear_color);
    }

    window.swapBuffers();
    glfw::pollEvents();
  }
}