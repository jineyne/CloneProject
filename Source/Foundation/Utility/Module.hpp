#pragma once

#include "Prerequisites/PrerequisitesUtil.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
#if COMPILER == COMPILER_MSVC
#   define TMODULE_IMPLEMENT(EXPORT_MACRO, CLASSNAME)
#else
#   define TMODULE_IMPLEMENT(EXPORT_MACRO, CLASSNAME) \
            template <> EXPORT_MACRO CLASSNAME *TModule<CLASSNAME>::mInstance = nullptr;        \
            template <> EXPORT_MACRO bool TModule<CLASSNAME>::mIsStartedUp = false;             \
            template <> EXPORT_MACRO bool TModule<CLASSNAME>::mIsDestroyed = false;
#endif
    /** 
     * 하나의 엔진 모듈입니다.
     * 본질은 특수한 유형의 싱글톤이라 사용 전후에 직접 생성하고 종료해야합니다.
     */
    template<typename T>
    class TModule : public NonCopyable {
#if COMPILER != COMPILER_MSVC
        static T *mInstance;
        static bool mIsStartedUp;
        static bool mIsDestroyed;
#endif
    public:
        /**
         * 모듈 객체의 참조를 반환합니다. 
         * @warning 모듈이 실행중이 아니라면 에러를 출력하고 프로그램이 종료됩니다.
         */
        static T &Instance() {
            if (!IsStartedUp()) {
                Debug::LogFatal("Trying to access not start module!");
            }

            if (IsDestroyed()) {
                Debug::LogFatal("Trying to access destroyed module!");
            }

            return *_Instance();
        }


        /**
         * 모듈을 주어진 인자와 함께 생성합니다.
         * @warning 모듈이 실행 중이 아니라면 에러를 출력하고 프로그램이 종료됩니다.
         */
        template <class ...Args>
        static void StartUp(Args &&...args) {
            if (IsStartedUp()) {
                Debug::LogFatal("Trying to start up module already started");
            }

            if (IsDestroyed()) {
                Debug::LogFatal("Trying to start up module already destroyed");
            }

            _Instance() = Allocator::New<T>(std::forward<Args>(args)...);
            static_cast<TModule<T> *>(_Instance())->onStartUp();

            IsStartedUp() = true;
        }

        /**
         * 모듈을 주어진 하위 시스템과 인자로 생성합니다.
         * @warning 모듈이 실행 중이 아니라면 에러를 출력하고 프로그램이 종료됩니다.
         */
        template <typename U, class ...Args>
        static void StartUp(Args &&...args) {
            if (IsStartedUp()) {
                Debug::LogFatal("Trying to start up module already started");
            }

            if (IsDestroyed()) {
                Debug::LogFatal("Trying to start up module already destroyed");
            }

            _Instance() = Allocator::New<U>(std::forward<Args>(args)...);
            static_cast<TModule<T> *>(_Instance())->onShutDown();

            IsStartedUp() = true;
        }

        /**
         * 모듈을 종료합니다.
         * @warning 모듈이 실행 중이 아니라면 에러를 출력하고 프로그램이 종료됩니다.
         */
        static void ShutDown() {
            if (!IsStartedUp()) {
                Debug::LogFatal("Trying to shut down module start yet");
            }

            if (IsDestroyed()) {
                Debug::LogFatal("Trying to shut down module already shut down");
            }

            static_cast<TModule<T> *>(_Instance())->onShutDown();
            Allocator::Free(_Instance());

            _Instance() = nullptr;
            IsDestroyed() = true;
        }

        /**
         * 모듈이 실행 중인지 확인합니다.
         */
        static bool IsRunning() {
            return IsStartedUp() && !IsDestroyed();
        }

    protected:
        /**
         * 모듈 생성 직후에 호출됩니다.
         * @note 할당 직후에 처리해야할 문제가 있다면 해당 함수를 재정의 하세요.
         */
        virtual void onStartUp() {}

        /**
         * 모듈 해제 직전에 호출됩니다.
         * @note 해제 직전에 처리해야할 문제가 있다면 해당 함수를 재정의 하세요.
         */
        virtual void onShutDown() {}

    private:
        static T *&_Instance() {
#if COMPILER == COMPILER_MSVC
            static T *inst = nullptr;
            return inst;
#else 
            return mInstance;
#endif
        }

        static bool &IsStartedUp() {
#if COMPILER == COMPILER_MSVC
            static bool inst = false;
            return inst;
#else
            return mIsStartedUp;
#endif
        }

        static bool &IsDestroyed() {
#if COMPILER == COMPILER_MSVC
            static bool inst = false;
            return inst;
#else
            return mIsDestroyed;
#endif
        }
    };
}
