#pragma once

#include "cpf.hpp"

#include "Scene/Object.hpp"

namespace cpf {
    class DLL_EXPORT Actor : public Object {
    protected:

    public:
        Actor(const String &name, uint32_t flags = 0x0);
        virtual ~Actor();

    public:
        void destroy(bool immediate = false) override;

    protected:
        void initialize(uint32_t id) override;
        void destroyInternal(bool immediate = false);

    private:
        friend class ActorManager;

        DECL_RUNTIMECLASS(Actor);
    };
}
