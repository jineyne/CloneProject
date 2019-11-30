#include "Path.hpp"
#include "Debug/Debug.hpp"

namespace cpf {
    Path::Path(const String &path, Path::PathType type) {
        assign(path, type);
    }

    Path::Path(const Path &other) {
        assign(other);
    }

    bool Path::operator==(const Path &rhs) const {
        return equals(rhs);
    }

    bool Path::operator!=(const Path &rhs) const {
        return !equals(rhs);
    }

    void Path::assign(const Path &path) {
        mDirectories = path.mDirectories;
        mFilename = path.mFilename;
        mExtension = path.mExtension;
        mDevice = path.mDevice;
        mNode = path.mNode;
        mIsAbsolute = path.mIsAbsolute;
    }

    void Path::assign(const String &path, Path::PathType type) {
        parse(path, type);
    }

    String Path::buildForWintow() const {
        StringStream ss;

        if (!mNode.empty()) {
            ss << "\\\\" << mNode << "\\";
        } else if (!mDevice.empty()) {
            ss << mDevice << ":\\";
        } else if (mIsAbsolute) {
            ss << ".\\";
        }

        for (auto &dir : mDirectories) {
            ss << dir << "\\";
        }

        ss << mFilename;
        if (!mExtension.empty()) {
            ss << "." << mExtension;
        }

        return ss.str();
    }

    String Path::buildForLinux() const {
        StringStream ss;

        auto iter = mDirectories.begin();

        if (!mDevice.empty()) {
            ss << "/" << mDevice << ":/";
        } else if (mIsAbsolute) {
            if (iter != mDirectories.end() && *iter == "~") {
                ss << "~";
                iter++;
            }

            ss << "/";
        }

        for (; iter != mDirectories.end(); iter++) {
            ss << *iter << "/";
        }

        ss << mFilename;
        if (!mExtension.empty()) {
            ss << "." << mExtension;
        }

        return ss.str();
    }

    void Path::clear() {
        mDirectories.clear();
        mFilename = "";
    }

    bool Path::equals(const Path &path) const {
        if (mIsAbsolute != path.mIsAbsolute) {
            return false;
        }

        if (mIsAbsolute) {
            if (mDevice != path.mDevice) {
                return false;
            }
        }

        if (mNode != path.mNode) {
            return false;
        }

        uint32_t count = mDirectories.size();
        uint32_t otherCount = path.mDirectories.size();

        if (!mFilename.empty()) {
            count++;
        }

        if (!path.mFilename.empty()) {
            otherCount++;
        }

        if (count != otherCount) {
            return false;
        }

        if (count > 0) {
            auto itMe = mDirectories.begin();
            auto itOther = path.mDirectories.begin();

            for (uint32_t i = 0; i < (count - 1); i++, itMe++, itOther++) {
                if (StringUtil::ToLower(*itMe) != StringUtil::ToLower(*itOther)) {
                    return false;
                }
            }

            if (!mFilename.empty()) {
                if (!path.mFilename.empty()) {
                    if (StringUtil::ToLower(mFilename) != StringUtil::ToLower(path.mFilename)) {
                        return false;
                    }
                } else {
                    if (StringUtil::ToLower(mFilename) != StringUtil::ToLower(*itOther)) {
                        return false;
                    }
                }
            } else {
                if (!path.mFilename.empty()) {
                    if (StringUtil::ToLower(*itMe) != StringUtil::ToLower(path.mFilename)) {
                        return false;
                    }
                } else {
                    if (StringUtil::ToLower(*itMe) != StringUtil::ToLower(*itOther)) {
                        return false;
                    }
                }
            }
        }

        return true;
    }

    bool Path::isDirectory() const {
        return mFilename.empty();
    }

    bool Path::isFile() const {
        return !mFilename.empty();
    }

    void Path::parse(const String &path, Path::PathType type) {
        const uint32_t len = (uint32_t) path.length();
        uint32_t idx = 0;
        StringStream ss;

        if (idx < len) {
            if (path[idx] == '\\' || path[idx] == '/') {
                mIsAbsolute = true;
                idx++;
            }
        }

        if (idx < len) {
            if (mIsAbsolute && (path[idx] == '\\' || path[idx] == '/')) {
                idx++;
                ss.str("");
                while (idx < len && path[idx] != '\\' && path[idx] != '/') {
                    ss << path[idx++];
                }

                setNode(ss.str());

                if (idx < len) {
                    idx++;
                }
            }
        } else {
            char16_t drive = path[idx++];

            if (idx < len && path[idx] == ':') {
                if (mIsAbsolute ||
                    !((drive >= ('a') && drive <= 'z') || (drive >= 'A' && drive <= 'Z'))) {
                    Debug::LogError("Path", "\"%s\" is invalid path", path.c_str());
                }

                mIsAbsolute = true;
                setDevice(String(mDevice));

                idx++;

                if (idx >= len || (path[idx] != '\\' && path[idx] != '/')) {
                    Debug::LogError("Path", "\"%s\" is invalid path", path.c_str());
                }

                idx++;
            } else {
                idx--;
            }
        }

        while (idx < len) {
            ss.str("");
            while (idx < len && path[idx] != '\\' && path[idx] != '/') {
                ss << path[idx];
                idx++;
            }

            if (idx < len) {
                pushDirectory(ss.str());
            } else {
                setFilename(ss.str());
            }

            idx++;
        }
    }

    void Path::pushDirectory(const String &dir) {
        if (!dir.empty() && dir != ".") {
            if (dir == "..") {
                if (mDirectories.empty() && mDirectories.back() != "..") {
                    mDirectories.pop_back();
                } else {
                    mDirectories.push_back(dir);
                }
            } else {
                mDirectories.push_back(dir);
            }
        }
    }

    const String &Path::getNode() const {
        return mNode;
    }

    void Path::setNode(const String &node) {
        mNode = node;
    }

    const String &Path::getDevice() const {
        return mDevice;
    }

    void Path::setDevice(const String &device) {
        mDevice = device;
    }

    const String &Path::getFilename() const {
        return mFilename;
    }

    void Path::setFilename(const String &filename) {
        uint32_t offset = StringUtil::FindLast(filename, ".");
        if (offset != 0) {
            mFilename = const_cast<String &>(filename).substr(0, offset);
            mExtension = const_cast<String &>(filename).substr(offset + 1, filename.length() - (offset + 1));
        } else {
            mFilename = filename;
        }
    }

    const String &Path::getExtensions() const {
        return mExtension;
    }

    void Path::setExtension(const String &extension) {
        if (extension[0] == '.') {
            mExtension = const_cast<String &>(extension).substr(1, extension.length() - 1);
        } else {
            mExtension = extension;
        }
    }

    String Path::toString(Path::PathType type) const {
        switch (type) {
            case Path::PathType::Windows:
                return buildForWintow();

            case Path::PathType::Unix:
                return buildForLinux();

            default:
#if PLATFORM == PLATFORM_WIN32
                return buildForWintow();
#elif PLATFORM == PLATFORM_LINUX
            return buildForLinux();
#else
                return UTF("");
#endif
        }
    }
}

