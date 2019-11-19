set(CPF_ALLOC_INC
    "Alloc/System.hpp")
set(CPF_ALLOC_SRC
    )

set(CPF_DEBUG_INC
    "Debug/Debug.hpp")
set(CPF_DEBUG_SRC
    "Debug/Debug.cpp")

set(CPF_MANAGER_INC
    "Manager/RenderWindowManager.hpp")
set(CPF_MANAGER_SRC
    "Manager/RenderWindowManager.cpp")

set(CPF_MATH_INC
    "Math/Math.hpp"
    "Math/Quaternion.hpp"
    "Math/Vector2.hpp"
    "Math/Vector3.hpp")
set(CPF_MATH_SRC
    "Math/Math.cpp"
    "Math/Quaternion.cpp"
    "Math/Vector2.cpp"
    "Math/Vector3.cpp")

set(CPF_PREREQUISITES_INC
    "Prerequisites/PlatformDefines.hpp"
    "Prerequisites/PrerequisitesUtil.hpp"
    "Prerequisites/StdHeaders.hpp")
set(CPF_PREREQUISITES_SRC)

set(CPF_RENDERING_INC
    "Rendering/RenderTarget.hpp"
    "Rendering/RenderWindow.hpp")
set(CPF_RENDERING_SRC
    "Rendering/RenderTarget.cpp"
    "Rendering/RenderWindow.cpp")

set(CPF_STRING_INC
    "String/String.hpp")
set(CPF_STRING_SRC
    "String/String.cpp")

set(CPF_UTILITY_INC
    "Utility/Module.hpp"
    "Utility/NonCopyable.hpp")
set(CPF_UTILITY_SRC
    )

set(CPF_NOFILTER_INC
    "Application.hpp"
    "cpf.hpp")
set(CPF_NOFILTER_SRC
    "Application.cpp")

set(CPF_SRCS 
    ${CPF_ALLOC_INC} ${CPF_ALLOC_SRC}
    ${CPF_DEBUG_INC} ${CPF_DEBUG_SRC}
    ${CPF_MANAGER_INC} ${CPF_MANAGER_SRC}
    ${CPF_MATH_INC} ${CPF_MATH_SRC}
    ${CPF_PREREQUISITES_INC} ${CPF_PREREQUISITES_SRC}
    ${CPF_RENDERING_INC} ${CPF_RENDERING_SRC}
    ${CPF_STRING_INC} ${CPF_STRING_SRC}
    ${CPF_UTILITY_INC} ${CPF_UTILITY_SRC}
    ${CPF_NOFILTER_INC} ${CPF_NOFILTER_SRC})
