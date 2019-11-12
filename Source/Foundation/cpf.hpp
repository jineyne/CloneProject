#pragma once

#include "Prerequisites/PrerequisitesUtil.hpp"

#include "String/String.hpp"

namespace cgf {
    template<class T>
    using SPtr = std::shared_ptr<T>;
    template<class T>
    using UPtr = std::unique_ptr<T>;

    class RenderTarget;
    using HRenderTarget = SPtr<RenderTarget>;
    class Application;
}
