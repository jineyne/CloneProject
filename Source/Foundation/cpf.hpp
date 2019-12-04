#pragma once

#include "Prerequisites/PrerequisitesUtil.hpp"

#include "String/String.hpp"

namespace cpf {
    template<class T>
    using SPtr = std::shared_ptr<T>;
    template<class T>
    using UPtr = std::unique_ptr<T>;

    class DataStream;
    class FileSystem;
    class Path;

    class ObjectManager;
    class RenderWindowManager;
    class SceneManager;

    class Math;
    class Matrix3;
    class Matrix4;
    class Quaternion;

    class Buffer;
    class GpuBuffer;
    class IndexBuffer;
    class RenderAPI;
    class RenderTarget;
    class RenderWindow;
    class Shadow;
    class UniformBuffer;
    class VertexBuffer;

    class RenderTarget;
    using HRenderTarget = SPtr<RenderTarget>;
    class RenderWindow;
    using HRenderWindow = SPtr<RenderWindow>;

    class Actor;
    class Object;
    class Scene;

    class Application;
}
