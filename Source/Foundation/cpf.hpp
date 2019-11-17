#pragma once

#include "Prerequisites/PrerequisitesUtil.hpp"

#include "String/String.hpp"

namespace cpf {
    template<class T>
    using SPtr = std::shared_ptr<T>;
    template<class T>
    using UPtr = std::unique_ptr<T>;

    class RenderTarget;
    using HRenderTarget = SPtr<RenderTarget>;
    class Application;
}
