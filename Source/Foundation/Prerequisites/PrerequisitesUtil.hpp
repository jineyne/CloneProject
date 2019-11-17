#pragma once

#include <assert.h>

#include "PlatformDefines.hpp"

#if defined(DEBUG) || defined(_DEBUG)
#   define DEBUG_MODE 1
#else
#   define DEBUG_MODE 0
#endif

#if DEBUG_MODE
#   define DEBUG_ONLY(exp) exp
#   define ASSERT(exp) exp
#else
#   define DEBUG_ONLY(exp)
#   define ASSERT(exp)
#endif

#include "StdHeaders.hpp"
#include "Alloc/System.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
