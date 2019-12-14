#pragma once

#include "cpf.hpp"

#include "Math/Matrix4.hpp"
#include "Math/Quaternion.hpp"
#include "Math/Vector3.hpp"

#include "Utility/Flags.hpp"

namespace cpf {
    class DLL_EXPORT Transform {
    private:
        Vector3 mPosition;
        Quaternion mRotation;
        Vector3 mScale;

    public:
        Transform();
        ~Transform() = default;

    public:
        void setPosition(const Vector3 &pos);
        void setRotation(const Quaternion &rot);
        void setScale(const Vector3 &scale);

        void move(const Vector3 &value);
        void rotate(const Quaternion &value);
        void scale(const Vector3 &value);

        Matrix4 getMatrix() const;
    };
}
