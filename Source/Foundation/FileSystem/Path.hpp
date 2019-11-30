#pragma once

#include "cpf.hpp"

namespace cpf {
    class DLL_EXPORT Path {
    public:
        enum class PathType {
            Windows,
            Unix,
            Default,
        };

    private:
        std::vector<String> mDirectories;

        String mNode;

        String mDevice;

        String mFilename;

        String mExtension;

        bool mIsAbsolute;

    public:
        Path() = default;

        Path(const String &path, PathType type = PathType::Default);

        Path(const Path &other);

        ~Path() = default;

    public:
        bool operator==(const Path &rhs) const;

        bool operator!=(const Path &rhs) const;

    public:
        void assign(const Path &path);
        void assign(const String &path, PathType type = PathType::Default);

        String buildForWintow() const;
        String buildForLinux() const;

        void clear();

        bool equals(const Path &path) const;

        bool isDirectory() const;
        bool isFile() const;

        void parse(const String &path, PathType type = PathType::Default);
        void pushDirectory(const String &dir);

        const String &getNode() const;
        void setNode(const String &node);

        const String &getDevice() const;
        void setDevice(const String &device);

        const String &getFilename() const;
        void setFilename(const String &filename);

        const String &getExtensions() const;
        void setExtension(const String &extensions);

        String toString(PathType type = PathType::Default) const;
    };
}

namespace std {
    template<>
    struct hash<cpf::Path> {
        std::size_t operator()(const cpf::Path &path) const {
            auto h = hash<cpf::String>{};
            return h(path.toString());
        }
    };
}

