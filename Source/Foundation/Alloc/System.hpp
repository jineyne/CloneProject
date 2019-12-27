#pragma once

namespace cpf {
    class Allocator {
    public:
        template <typename T>
        static T *Alloc(uint32_t num = 1) {
            return static_cast<T *>(malloc(sizeof(T) * num));
        }

        template <typename T>
        static void Free(T *ptr) {
            free(ptr);
        }

        template <typename T, class ...Args>
        static T *New(Args &&... args) {
            return new (Alloc<T>()) T(std::forward<Args>(args)...);
        }

        template <typename T>
        static void Delete(T *ptr) {
            ptr->~T();
            Free(ptr);
        }

        template <typename T, class ...Args>
        static std::shared_ptr<T> SharedPtr(Args &&...args) {
            return std::shared_ptr<T>(std::forward<Args>(args)...);
        }

        template <typename T, class ...Args>
        static std::shared_ptr<T> MakeShared(Args &&...args) {
            return SharedPtr<T>(Allocator::New<T>(std::forward<Args>(args)...));
        }
    };
}
