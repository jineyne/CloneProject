#pragma once

#include "cpf.hpp"

#include "Scene/Object.hpp"

namespace cpf {
    class DLL_EXPORT Actor : public Object {
    private:
        std::vector<Actor *> mChildActorList {};
        Actor *mParentActor = nullptr;

    public:
        Actor(const String &name, uint32_t flags = 0x0);
        virtual ~Actor();

    public:
        bool operator==(Actor *actor);

    public:
        void startUp();
        void shutDown();
        void update();

        void destroy(bool immediate = false) override;

        void setParent(Actor *actor);
        
        void addChild(Actor *actor);
        void removeChild(Actor *actor);

        bool equals(Actor *actor) const;

    protected:
        // @copydoc Object::initialize
        void initialize(uint32_t id) override;

        // @copydoc Object::destroyInternal
        void destroyInternal(bool immediate = false) override;

        virtual void onStartUp() {}
        virtual void onShutDown() {}
        virtual void onUpdate() {}

        DECL_RUNTIMECLASS(Actor);
    };
}
