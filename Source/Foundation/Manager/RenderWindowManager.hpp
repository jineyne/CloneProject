#pragma once

#include "cpf.hpp"

#include "Rendering/RenderWindow.hpp"
#include "Utility/Module.hpp"

namespace cpf {
    class DLL_EXPORT RenderWindowManager : public TModule<RenderWindowManager> {
    private:
        std::unordered_map<uint32_t, HRenderWindow> mRenderWindowList;
        uint32_t mNextWindowId = 1;

    public:
        RenderWindowManager() = default;
        ~RenderWindowManager() = default;

    public:
        HRenderWindow initialize(const RenderWindowCreateInfo &info);

        HRenderWindow create(const RenderWindowCreateInfo &info);

        void update();

        const HRenderWindow &getWindow(uint32_t id) const;

    private:
        friend class RenderWindow;

        static void WindowCloseRequest(GLFWwindow *window);
    };
}
