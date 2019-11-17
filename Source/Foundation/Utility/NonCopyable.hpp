#pragma once

namespace cpf {
    /**
     * 복사를 차단하는 클래스입니다.
     */
    class NonCopyable {
	public:
		NonCopyable() = default;

		NonCopyable(const NonCopyable &) = delete;
		NonCopyable &operator=(const NonCopyable &) = delete;
    };
}
