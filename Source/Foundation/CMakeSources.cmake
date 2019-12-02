set(CPF_ALLOC_INC
    "Alloc/System.hpp")
set(CPF_ALLOC_SRC
    )

set(CPF_DEBUG_INC
    "Debug/Debug.hpp")
set(CPF_DEBUG_SRC
    "Debug/Debug.cpp")

set(CPF_FILESYSTEM_INC
    "FileSystem/DataStream.hpp"
    "FileSystem/FileSystem.hpp"
    "FileSystem/Path.hpp")
set(CPF_FILESYSTEM_SRC
    "FileSystem/DataStream.cpp"
    "FileSystem/FileSystem.cpp"
    "FileSystem/Path.cpp")

set(CPF_MANAGER_INC
    "Manager/ObjectManager.hpp"
    "Manager/RenderWindowManager.hpp")
set(CPF_MANAGER_SRC
    "Manager/ObjectManager.cpp"
    "Manager/RenderWindowManager.cpp")

set(CPF_MATH_INC
    "Math/Math.hpp"
    "Math/Matrix3.hpp"
    "Math/Matrix4.hpp"
    "Math/Quaternion.hpp"
    "Math/Vector2.hpp"
    "Math/Vector3.hpp")
set(CPF_MATH_SRC
    "Math/Math.cpp"
    "Math/Matrix3.cpp"
    "Math/Matrix4.cpp"
    "Math/Quaternion.cpp"
    "Math/Vector2.cpp"
    "Math/Vector3.cpp")

set(CPF_PREREQUISITES_INC
    "Prerequisites/PlatformDefines.hpp"
    "Prerequisites/PrerequisitesUtil.hpp"
    "Prerequisites/StdHeaders.hpp")
set(CPF_PREREQUISITES_SRC)

set(CPF_RENDERAPI_INC
    "RenderAPI/Buffer.hpp"
    "RenderAPI/GpuBuffer.hpp"
    "RenderAPI/IndexBuffer.hpp"
    "RenderAPI/RenderAPI.hpp"
    "RenderAPI/RenderTarget.hpp"
    "RenderAPI/RenderWindow.hpp"
    "RenderAPI/Shader.hpp"
    "RenderAPI/UniformBuffer.hpp"
    "RenderAPI/VertexBuffer.hpp")
set(CPF_RENDERAPI_SRC
    "RenderAPI/Buffer.cpp"
    "RenderAPI/GpuBuffer.cpp"
    "RenderAPI/IndexBuffer.cpp"
    "RenderAPI/RenderAPI.cpp"
    "RenderAPI/RenderTarget.cpp"
    "RenderAPI/RenderWindow.cpp"
    "RenderAPI/Shader.cpp"
    "RenderAPI/UniformBuffer.cpp"
    "RenderAPI/VertexBuffer.cpp")

set(CPF_SCENE_INC
    "Scene/Actor.hpp"
    "Scene/Object.hpp"
    "Scene/Scene.hpp")
set(CPF_SCENE_SRC
    "Scene/Actor.cpp"
    "Scene/Object.cpp"
    "Scene/Scene.cpp")

set(CPF_STRING_INC
    "String/String.hpp")
set(CPF_STRING_SRC
    "String/String.cpp")

set(CPF_UTILITY_INC
    "Utility/Flags.hpp"
    "Utility/Module.hpp"
    "Utility/NonCopyable.hpp"
    "Utility/RuntimeClass.hpp")
set(CPF_UTILITY_SRC
    "Utility/RuntimeClass.cpp")

set(CPF_NOFILTER_INC
    "Application.hpp"
    "cpf.hpp")
set(CPF_NOFILTER_SRC
    "Application.cpp")

set(CPF_WIN32_INC
    "Private/Win32/Win32.hpp")
set(CPF_WIN32_SRC
    "Private/Win32/Win32Path.cpp")

set(CPF_SRCS 
    ${CPF_ALLOC_INC} ${CPF_ALLOC_SRC}
    ${CPF_DEBUG_INC} ${CPF_DEBUG_SRC}
    ${CPF_FILESYSTEM_INC} ${CPF_FILESYSTEM_SRC}
    ${CPF_MANAGER_INC} ${CPF_MANAGER_SRC}
    ${CPF_MATH_INC} ${CPF_MATH_SRC}
    ${CPF_PREREQUISITES_INC} ${CPF_PREREQUISITES_SRC}
    ${CPF_RENDERAPI_INC} ${CPF_RENDERAPI_SRC}
    ${CPF_SCENE_INC} ${CPF_SCENE_SRC}
    ${CPF_STRING_INC} ${CPF_STRING_SRC}
    ${CPF_UTILITY_INC} ${CPF_UTILITY_SRC}
    ${CPF_NOFILTER_INC} ${CPF_NOFILTER_SRC})

if(WIN32) 
    list(APPEND CPF_SRCS ${CPF_WIN32_INC} ${CPF_WIN32_SRC})
endif()
