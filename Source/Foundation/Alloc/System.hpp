#pragma once

namespace cpf {
    /**
     * 메모리 할당을 도와줄 핼퍼 클래스입니다.
     */
    class Allocator {
    public:
        /**
         * 주어진 타입을 num만큼 생성합니다.
         * @tparam T 생성할 타입.
         * @param num 생성할 수량. 기본 값은 1입니다.
         */
        template <typename T>
        static T *Alloc(uint32_t num = 1) {
            return static_cast<T *>(malloc(sizeof(T) * num));
        }

        /**
         * 주어진 객체를 해제시킵니다.
         */
        template <typename T>
        static void Free(T *ptr) {
            free(ptr);
        }

        /**
         * 주어진 타입을 인자로 생성합니다.
         */
        template <typename T, class ...Args>
        static T *New(Args &&... args) {
            return new (Alloc<T>()) T(std::forward<Args>(args)...);
        }

        /**
         * 주어진 객체를 파괴자 호출 후 해제합니다.
         */
        template <typename T>
        static void Delete(T *ptr) {
            ptr->~T();
            Free(ptr);
        }

        /**
         * 주어진 인자를 shared_ptr로 변환합니다.
         * @warning 주어진 인자를 가지고 shared_ptr을 생성하려면 MakeShared를 사용하세요.
         */
        template <typename T, class ...Args>
        static std::shared_ptr<T> SharedPtr(Args &&...args) {
            return std::shared_ptr<T>(std::forward<Args>(args)...);
        }

        /**
         * 주어진 인자를 통해 shared_ptr을 생성합니다.
         *
         * @tparam T shared_ptr의 타입입니다.
         * @param args T 타입의 생성자에 들어갈 인자들입니다.
         */
        template <typename T, class ...Args>
        static std::shared_ptr<T> MakeShared(Args &&...args) {
            return SharedPtr<T>(Allocator::New<T>(std::forward<Args>(args)...));
        }
    };
}
