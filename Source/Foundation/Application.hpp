#pragma once

#include "cpf.hpp"

#include "RenderAPI/RenderWindow.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    struct ApplicationCreateInfo {
        RenderWindowCreateInfo primaryWindowCreateInfo;
    };

    class DLL_EXPORT Application : public TModule<Application> {
    protected:
        ApplicationCreateInfo mInfo;

        HRenderWindow mPrimaryWindow;
        bool mIsRunning;

    public:
        Application(const ApplicationCreateInfo &info);
        virtual ~Application();

    public:
        void runMainLoop();

        void stopMainLoop();

        void quitRequest();

        HRenderWindow getPrimaryWindow() { return mPrimaryWindow; }

    protected:
        void onStartUp() override;
        void onShutDown() override;

    private:
        void initializeCore();
        void destroyCore();
    };
}
