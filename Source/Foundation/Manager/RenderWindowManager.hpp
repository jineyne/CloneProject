#pragma once

#include "cpf.hpp"

#include "Rendering/RenderWindow.hpp"
#include "Utility/Module.hpp"

namespace cpf {
    /**
     * 윈도우를 컨트롤하는 매니저 모듈입니다.
     */
    class DLL_EXPORT RenderWindowManager : public TModule<RenderWindowManager> {
    private:
        std::unordered_map<uint32_t, HRenderWindow> mRenderWindowList; //< 윈도우 식별자를 키로 가지고 있는 맵

        //< 다음 윈도우의 식별자를 보유하고 있습니다. 0은 초기화되지 않은 윈도우가 가지는 식별자입니다.
        uint32_t mNextWindowId = 1; 

    public:
        RenderWindowManager() = default;
        ~RenderWindowManager() = default;

    public:
        /**
         * 윈도우를 생성 후 초기화가 필요한 라이브러리를 초기화합니다.
         * @brief
         *  초기화 할때 윈도우가 필요한 라이브러리를 추가적으로 초기화하는 과정을 거칩니다.
         */
        HRenderWindow initialize(const RenderWindowCreateInfo &info);

        // 윈도우를 주어진 정보를 통해 생성합니다.
        HRenderWindow create(const RenderWindowCreateInfo &info);

        // 윈도우 및 윈도우 관련 라이브러리를 업데이트합니다.
        void update();

        // 윈도우 식별자로 해당 윈도우의 핸들을 얻습니다.
        const HRenderWindow &getWindow(uint32_t id) const;

    private:
        friend class RenderWindow;

        // 윈도우의 닫기 요청 이벤트를 처리합니다.
        static void WindowCloseRequest(GLFWwindow *window);
    };
}
