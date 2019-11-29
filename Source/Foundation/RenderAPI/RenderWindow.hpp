#pragma once

#include "cpf.hpp"

#include "RenderAPI/RenderTarget.hpp"

namespace cpf {
    /**
     * 랜더 윈도우를 만들 때 필요로하는 정보들입니다.
     * @todo 윈도우 크기를 VideoMode로 변경할 예정입니다.
     */
    struct RenderWindowCreateInfo {
        uint32_t width;             //< 윈도우 넓이
        uint32_t height;            //< 윈도우 높이
        String title = "";          //< 윈도우 타이틀
        bool fullscreen = false;    //< 윈도우 최대화 여부
    };

    /**
     * 직접적으로 그려지는 윈도우입니다.
     */
    class DLL_EXPORT RenderWindow : public RenderTarget {
    private:
        GLFWwindow *mWindowPtr;
        uint32_t mWindowId = 0; //< 윈도우 식별자

        RenderWindowCreateInfo mInfo;

    public:
        RenderWindow(const RenderWindowCreateInfo &info);
        ~RenderWindow();

    public:
        // 윈도우를 초기화합니다.
        void initialize(uint32_t id);

        // 윈도우 버퍼를 교체합니다.
        void swapBuffers(uint32_t mask) override;
    };
}
