#include "Camera.hpp"

namespace cpf {
    Camera::Camera(Actor *actor) : Component(actor, "Camera"), CameraBase() {}

    void Camera::onTransformChanged(const TransformChangedFlags &flags) {
        if (flags) {
            setTransform(mOwner->getLocalTransform());
            mDirtyFlags = true;
        }
    }
}
