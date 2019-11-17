#pragma once

#include "cpf.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    struct ApplicationCreateInfo {
        uint32_t width, height;
        String title;
    };

    class DLL_EXPORT Application : public TModule<Application> {
    protected:
        ApplicationCreateInfo mInfo;

        bool mIsRunning;

    public:
        Application(const ApplicationCreateInfo &info);
        virtual ~Application();

    public:
        void runMainLoop();

    protected:
        void onStartUp() override;
        void onShutDown() override;

    private:
        void initializeCore();
        void destroyCore();
    };
}
