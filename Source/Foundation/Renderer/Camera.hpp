#pragma once

#include "cpf.hpp"

#include "Math/Matrix4.hpp"

namespace cpf {
    enum class EProjectionType {
        Perspective,
        Orthograhic,
    };

    class DLL_EXPORT CameraBase {
    private:
        EProjectionType mProjectionType;
        float mNear, mFar;
        float mOrthoHeight;
        float mAspect;
        float mFov;

        bool mDirtyFlags = false;
        bool mIsMain = false;

        mutable Matrix4 mCachedView;

    public:
        CameraBase() = default;
        virtual ~CameraBase() = default;

    public:
        virtual void setNear(float value);
        virtual void setFar(float value);
        virtual void setFov(float fov);
        virtual void setAspect(float aspect);
        virtual void setOrthoHeight(float height);

        void setMain(bool main = true);
        bool isMain() const { return mIsMain; }

        virtual const Matrix4 &getViewMatrix();
    };
}
