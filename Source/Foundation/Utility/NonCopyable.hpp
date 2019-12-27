#pragma once

namespace cpf {
    class NonCopyable {
	public:
		NonCopyable() = default;

		NonCopyable(const NonCopyable &) = delete;
		NonCopyable &operator=(const NonCopyable &) = delete;
    };
}
