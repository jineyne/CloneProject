#pragma once

#include "cpf.hpp"

#include "Math/Matrix4.hpp"
#include "Scene/Transform.hpp"

namespace cpf {
    enum class EProjectionType {
        Perspective,
        Orthograhic,
    };

    class DLL_EXPORT CameraBase {
    protected:
        EProjectionType mProjectionType;

        float mNear, mFar;
        float mOrthoHeight;
        float mAspect;
        float mFov;

        bool mDirtyFlags = false;
        bool mIsMain = false;

        Transform mTransform;
        mutable Matrix4 mCachedView;

    public:
        CameraBase() = default;
        virtual ~CameraBase() = default;

    public:
        void setTransform(const Transform &transform);

        virtual void setNear(float value);
        virtual void setFar(float value);
        virtual void setFov(float fov);
        virtual void setAspect(float aspect);
        virtual void setOrthoHeight(float height);

        virtual void setProjectionType(EProjectionType type);

        void setMain(bool main = true);
        bool isMain() const { return mIsMain; }

        virtual const Matrix4 &getViewMatrix();
    };
}
