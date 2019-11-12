#pragma once

#include "cpf.hpp"

namespace cpf {
    class DLL_EXPORT Debug {
    public:
        template<typename ...Args>
        static void LogInfo(const String &fmt, Args&&...args) {
            std::cout << "INFO:\t\t"  << StringUtil::Format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        template<typename ...Args>
        static void LogWarning(const String &fmt, Args&&...args) {
            std::cout << "WARNING:\t" << StringUtil::Format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        template<typename ...Args>
        static void LogError(const String &fmt, Args&&...args) {
            std::cout << "ERROR:\t\t" << StringUtil::Format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        template<typename ...Args>
        static void LogFatal(const String &fmt, Args&&...args) {
            std::cout << "FATAL:\t\t" << StringUtil::Format(fmt, std::forward<Args>(args)...) << std::endl;
            exit(EXIT_FAILURE);
        }
    };
}
