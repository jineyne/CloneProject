#include "Camera.hpp"

#include "Renderer/Renderer.hpp"

namespace cpf {
    void CameraBase::setNear(float value) {
        mNear = value;

        mDirtyFlags = true;
    }

    void CameraBase::setFar(float value) {
        mFar = value;

        mDirtyFlags = true;
    }

    void CameraBase::setAspect(float aspect) {
        mAspect = aspect;

        mDirtyFlags = true;
    }
    void CameraBase::setFov(float fov) {
        mFov = fov;
        mDirtyFlags = true;
    }

    void CameraBase::setOrthoHeight(float height) {
        mOrthoHeight = height;

        mDirtyFlags = true;
    }
    
    void CameraBase::setMain(bool main) {
        if (!mIsMain && main) {
            Renderer::Instance().notifyCameraChangeMain(this);
        }

        mIsMain = main;
    }

    const Matrix4 &CameraBase::getViewMatrix() {
        if (mDirtyFlags) {
            mDirtyFlags = false;

            uint32_t width = mOrthoHeight * mAspect;
            uint32_t height = mOrthoHeight;

            switch (mProjectionType) {
            case EProjectionType::Perspective:
                mCachedView = Matrix4::Perspective(mFov, mAspect, mNear, mFar);
                break;
            case EProjectionType::Orthograhic:
                mCachedView = Matrix4::Orthograhic(0, width, 0, height, mNear, mFar);
                break;
            }
        }

        return mCachedView;
    }
}
