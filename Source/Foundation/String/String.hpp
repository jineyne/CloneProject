#pragma once

#include <string>

#include "Prerequisites/PrerequisitesUtil.hpp"

namespace cpf {
	template<typename T>
    using BasicString = std::basic_string<T, std::char_traits<T>>;

    template<typename T>
    using BasicStringStream = std::basic_stringstream<T, std::char_traits<T>>;

    using String = BasicString<char>;
    using WString = BasicString<wchar_t>;
    using U16String = BasicString<char16_t>;
    using U32String = BasicString<char32_t>;

    using StringStream = BasicStringStream<char>;
    using WStringStream = BasicStringStream<wchar_t>;
    using U16StringStream = BasicStringStream<char16_t>;
    using U32StringStream = BasicStringStream<char32_t>;

    class DLL_EXPORT StringUtil {
    private:
        template<size_t Count>
        static inline void FormatArguments(std::array<std::string, Count> &fmt) {
            // base
        }

        template<size_t Count, typename T, typename...Args>
        static inline void FormatArguments(std::array<std::string, Count> &fmt, T &&arg, Args&&...args) {
            fmt[Count - 1 - sizeof...(args)] = ToString(arg);
            FormatArguments(fmt, std::forward<Args>(args)...);
        }

    public:
        template<typename T>
        static inline std::string ToString(const T &arg) {
            StringStream ss;
            ss << arg;
            return ss.str();
        }

        /**
         * 주어진 포멧에 맞게 인자들을 재배치시킵니다.
         * @brief
         *  {} => 해당 순서에 맞는 인자를 대입시킵니다.
         *  {n} => n에 해당하는 순서에 맞는 인자를 대입시킵니다.
         *
         * @todo
         *  해당 위치에 특정한 타입으로 대입 시킬 수 있는 포멧을 추가할 예정입니다.
         */
        template<typename ...Args>
        static String Format(const String &fmt, Args&&...arguments) {
            std::array<std::string, sizeof...(Args)> args;
            FormatArguments(args, std::forward<Args>(arguments)...);

            auto check = [&fmt](String::const_iterator it, std::function<bool(const char &ch)> fn) {
                return it != fmt.end() && fn(*it);
            };

            StringStream ss;
            StringStream tmp;
            uint32_t forceOfNature = 0;

            for (String::const_iterator it = fmt.begin(); it != fmt.end();) {
                if (check(it, [](const char &ch) -> bool { return ch == '{'; })) {
                    it++;
                    tmp.str("");

                    // check args
                    while (check(it, [](const char &ch) -> bool { return std::isdigit(ch); })) {
                        tmp << *it;
                        it++;
                    }

                    if (tmp.str().empty()) {
                        ss << args[forceOfNature];
                    } else {
                        int32_t index = std::atoi(tmp.str().c_str());
                        if (index < args.size()) {
                            ss << args[index];
                        } else {
                            std::cout << "ERROR: Out of range!" << std::endl 
                                << "Request index is " << index 
                                << ", but max args index is " << args.size() - 1 << std::endl;
                            return "";
                        }
    
                    }

                    if (!check(it++, [](const char &ch) -> bool { return ch == '}'; })) {
                        std::cout << "ERROR: Invalid token! " << *it << std::endl;
                        return "";
                    }

                    forceOfNature++;
                } else {
                    ss << *it;
                    it++;
                }
            }

            return ss.str();
        }
    };
}
