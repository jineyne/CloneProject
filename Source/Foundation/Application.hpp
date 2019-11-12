#pragma once

#include "cpf.hpp"

namespace cpf {
    struct ApplicationCreateInfo {
        uint32_t width, height;
        String title;
    };

    class DLL_EXPORT Application {
    protected:
        ApplicationCreateInfo mInfo;

        bool mIsRunning;

    public:
        Application(const ApplicationCreateInfo &info);
        virtual ~Application();

    public:
        void runMainLoop();

    private:
        void initializeCore();
        void destroyCore();
    };
}
