add_executable(main main.cpp)
target_link_libraries(main PRIVATE GLFWPP libglew_static Imgui)
target_compile_features(main PRIVATE cxx_std_20)
target_compile_definitions(main PRIVATE GLEW_STATIC)
if (MSVC)
	target_compile_options(main PRIVATE "/Zc:preprocessor")
endif()

add_subdirectory(shaders)