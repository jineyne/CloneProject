#include "RenderWindowManager.hpp"

#include "Application.hpp"

namespace cpf {
    TMODULE_IMPLEMENT(DLL_EXPORT, RenderWindowManager);

    HRenderWindow RenderWindowManager::initialize(const RenderWindowCreateInfo &info) {
        HRenderWindow window = create(info);

        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        return window;
    }
    
    HRenderWindow RenderWindowManager::create(const RenderWindowCreateInfo &info) {
        uint32_t id = mNextWindowId++; 
        HRenderWindow window = Allocator::MakeShared<RenderWindow>(info);
        window->initialize(id);

        mRenderWindowList.insert(std::make_pair(id, window));

        return window;
    }

    void RenderWindowManager::update() {
        glfwPollEvents();
    }

    const HRenderWindow &RenderWindowManager::getWindow(uint32_t id) const {
        auto it = mRenderWindowList.find(id);
        if (it != mRenderWindowList.end()) {
            return it->second;
        }

        return nullptr;
    }

    void RenderWindowManager::WindowCloseRequest(GLFWwindow *window) {
        Application::Instance().quitRequest();
    }
}
