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
    template<typename T>
    class TModule : public NonCopyable {
#if COMPILER != COMPILER_MSVC
        static T *mInstance;
        static bool mIsStartedUp;
        static bool mIsDestroyed;
#endif
    public:
        static T &Instance() {
            if (!IsStartedUp()) {
                Debug::LogFatal("Trying to access not start module!");
            }

            if (IsDestroyed()) {
                Debug::LogFatal("Trying to access destroyed module!");
            }

            return *_Instance();
        }

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

        static bool IsRunning() {
            return IsStartedUp() && !IsDestroyed();
        }

    protected:
        virtual void onStartUp() {}

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
