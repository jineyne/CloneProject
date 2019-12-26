#pragma once

#include "cpf.hpp"

#include "Math/Matrix4.hpp"

#include "Renderer/Camera.hpp"

#include "Scene/Actor.hpp"
#include "Scene/Component.hpp"

namespace cpf {
    class DLL_EXPORT Camera : public Component, public CameraBase {
    public:
        Camera(Actor *owner);
        ~Camera() = default;
    };
}
