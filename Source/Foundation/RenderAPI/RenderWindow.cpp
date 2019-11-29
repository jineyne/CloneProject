#include "RenderWindow.hpp"

#include "Manager/RenderWindowManager.hpp"

namespace cpf {
    RenderWindow::RenderWindow(const RenderWindowCreateInfo &info) 
        : mWindowPtr(nullptr), mInfo(info) {}

    RenderWindow::~RenderWindow() {}

    void RenderWindow::initialize(uint32_t id) {
        mWindowId = id;

        GLFWmonitor *monitor = nullptr;
        if (mInfo.fullscreen) {
            monitor = glfwGetPrimaryMonitor();
        }
        mWindowPtr = glfwCreateWindow(mInfo.width, mInfo.height, mInfo.title.c_str(), monitor, nullptr);
        glfwMakeContextCurrent(mWindowPtr);
        glfwSetWindowCloseCallback(mWindowPtr, RenderWindowManager::WindowCloseRequest);
    }

    void RenderWindow::swapBuffers(uint32_t mask) {
        glfwSwapBuffers(mWindowPtr);
    }
}
