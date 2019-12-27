#pragma once

#include "cpf.hpp"

#include "RenderAPI/RenderTarget.hpp"

namespace cpf {
    struct RenderWindowCreateInfo {
        uint32_t width;
        uint32_t height;
        String title = "";
        bool fullscreen = false;
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

        GLFWwindow *getWindowHandle() const { return mWindowPtr; }
    };
}
