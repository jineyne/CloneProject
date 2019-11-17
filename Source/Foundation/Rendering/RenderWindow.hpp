#pragma once

#include "cpf.hpp"

#include "RenderTarget.hpp"

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

    class DLL_EXPORT RenderWindow : public RenderTarget {
    private:
        GLFWwindow *mWindowPtr;
        uint32_t mWindowId = 0;

        RenderWindowCreateInfo mInfo;

    public:
        RenderWindow(const RenderWindowCreateInfo &info);
        ~RenderWindow();

    public:
        void initialize(uint32_t id);

        void swapBuffers(uint32_t mask) override;
    };
}
