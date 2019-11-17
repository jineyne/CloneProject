#pragma once

#include "cpf.hpp"

#include "Rendering/RenderWindow.hpp"

#include "Utility/Module.hpp"

namespace cpf {
    /**
     * 어플리케이션을 생성하는데 필요한 정보입니다.
     */
    struct ApplicationCreateInfo {
        //< 어플리케이션에서 생성되는 기본 윈도우 생성에 필요한 정보입니다.
        RenderWindowCreateInfo primaryWindowCreateInfo;
    };

    /**
     * 어플리케이션의 메인 모듈입니다.
     */
    class DLL_EXPORT Application : public TModule<Application> {
    protected:
        ApplicationCreateInfo mInfo;

        HRenderWindow mPrimaryWindow;
        bool mIsRunning;

    public:
        Application(const ApplicationCreateInfo &info);
        virtual ~Application();

    public:
        // 메인 루프를 돌게 만듭니다.
        void runMainLoop();

        // 메인 루프를 멈추게 만듭니다.
        void stopMainLoop();

        // 메인 루프를 멈추게 요청합니다.
        void quitRequest();

    protected:
        void onStartUp() override;
        void onShutDown() override;

    private:
        void initializeCore();
        void destroyCore();
    };
}
