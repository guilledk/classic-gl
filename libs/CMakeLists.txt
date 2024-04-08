cmake_policy(SET CMP0079 NEW)

# json
set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory("nlohmann-json")
target_link_libraries(classic_gl_app nlohmann_json::nlohmann_json)

# GL
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)
target_link_libraries(classic_gl_app ${OPENGL_LIBRARIES})

# GLFW
add_subdirectory(glfw)
target_link_libraries(classic_gl_app glfw)

# GLEW
find_package(glew REQUIRED)
target_link_libraries(classic_gl_app GLEW)
target_include_directories(classic_gl_app PUBLIC ${GLEW_INCLUDE_DIRS})

# stb
target_include_directories(classic_gl_app PUBLIC "stb")
