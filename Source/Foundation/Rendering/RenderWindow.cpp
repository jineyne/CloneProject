#include "RenderWindow.hpp"

namespace cpf {
    RenderWindow::RenderWindow(const RenderWindowCreateInfo &info) 
        : mWindowPtr(nullptr), mInfo(info) {}

    RenderWindow::~RenderWindow() {}

    void RenderWindow::initialize(uint32_t id) {
        mWindowId = id;

        GLFWmonitor *monitor = nullptr;
        if (mInfo.fullscreen) {
            monitor = glfwGetMonitor(0);
        }
        mWindowPtr = glfwCreateWindow(mInfo.width, mInfo.height, mInfo.title.c_str(), monitor, nullptr);
        glfwMakeContextCurrent(mWindowPtr);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    }

    void RenderWindow::swapBuffers(uint32_t mask) {
        glfwSwapBuffers(mWindowPtr);
    }
}
