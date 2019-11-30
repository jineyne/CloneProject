#include "String.hpp"

namespace cpf {
    String StringUtil::ToLower(String str) {
        // TODO: Fix error
        // std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
        return str;
    }

    uint32_t StringUtil::Find(const String &str, const String &token, uint32_t startPos) {
        for (uint32_t i = startPos; i < static_cast<int32_t>(str.size()); i++) {
            for (uint32_t j = 0; j < token.length(); j++) {
                if (str[i + j] != token[j]) {
                    goto not_same;
                }
            }

            return i;

            not_same:
            continue;
        }

        return -1;
    }

    uint32_t StringUtil::FindLast(const String &str, const String &token, uint32_t startPos) {
        for (int32_t i = static_cast<int32_t>(str.size()) - 1; i >= 0; i--) {
            for (int32_t j = token.length() - 1; j >= 0; j--) {
                if (str[i] != token[j]) {
                    goto not_same;
                }
            }

            return i;

            not_same:
            continue;
        }

        return -1;
    }

    std::vector<String> StringUtil::Split(const String &str, const String &token) {
        std::vector<String> result;
        uint32_t startPos = 0;
        uint32_t findPos = 0;
        while ((findPos = Find(str, token, startPos)) != static_cast<uint32_t>(-1)) {
            result.emplace_back(str.substr(startPos, findPos - startPos));
            startPos = findPos + 1;
        }

        if (startPos < str.size()) {
            result.emplace_back(str.substr(startPos, str.size() - startPos));
        }

        return result;
    }
}
