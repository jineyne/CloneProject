project(Sandbox)

include(CMakeSources.cmake)

add_executable(Sandbox ${SANDBOX_SRCS})
set_project_options(Sandbox)
