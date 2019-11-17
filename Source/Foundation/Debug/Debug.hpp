#pragma once

#include "cpf.hpp"

namespace cpf {
    /**
     *  디버깅에 사용할 함수들을 모아놓은 핼퍼 클래스입니다.
     */
    class DLL_EXPORT Debug {
    public:
        /**
         * 개발, 운영에 도움을 줄 정보를 출력합니다.
         */
        template<typename ...Args>
        static void LogInfo(const String &fmt, Args&&...args) {
            std::cout << "INFO:\t\t"  << StringUtil::Format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        /**
         * 비정상적인 상황에 맞닥쳤지만 해결할 수 있는 상황의 정보를 출력합니다.
         */
        template<typename ...Args>
        static void LogWarning(const String &fmt, Args&&...args) {
            std::cout << "WARNING:\t" << StringUtil::Format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        /**
         * 비정상적인 상황에 맞닥쳤고 부분적으로 오작동 했을 경우가 높은 상황의 정보를 출력합니다.
         */
        template<typename ...Args>
        static void LogError(const String &fmt, Args&&...args) {
            std::cout << "ERROR:\t\t" << StringUtil::Format(fmt, std::forward<Args>(args)...) << std::endl;
        }

        /**
         * 비정상적인 상황에 맞닥쳤고 복구 불가능한 상황의 정보를 출력합니다.
         */
        template<typename ...Args>
        static void LogFatal(const String &fmt, Args&&...args) {
            std::cout << "FATAL:\t\t" << StringUtil::Format(fmt, std::forward<Args>(args)...) << std::endl;
            exit(EXIT_FAILURE);
        }
    };
}
