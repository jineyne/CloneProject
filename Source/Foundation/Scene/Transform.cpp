#include "Transform.hpp"

namespace cpf {
    Transform::Transform() : mPosition(0, 0, 0), mRotation(), mScale(1, 1, 1) {}

    void Transform::setPosition(const Vector3 &pos) {
        mPosition = pos;
    }

    void Transform::setRotation(const Quaternion &rot) {
        mRotation = rot;
    }

    void Transform::setScale(const Vector3 &scale) {
        mScale = scale;
    }

    void Transform::move(const Vector3 &value) {
        mPosition += value;
    }

    void Transform::rotate(const Quaternion &value) {
        mRotation += value;
    }

    void Transform::scale(const Vector3 &value) {
        mScale += value;
    }

    Matrix4 Transform::getMatrix() const {
        Matrix4 pos = Matrix4::Translation(mPosition);
        Matrix4 rot = Matrix4::Rotation(mRotation);
        Matrix4 scl = Matrix4::Scaling(mScale);

        Matrix4 m = scl * rot * pos;

        return m;
    }
}
