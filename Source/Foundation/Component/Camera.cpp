#include "Camera.hpp"

namespace cpf {
    Camera::Camera(Actor *actor) : Component(actor, "Camera"), CameraBase() {}
}
