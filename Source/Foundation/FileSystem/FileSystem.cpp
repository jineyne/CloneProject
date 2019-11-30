#include "FileSystem.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    std::shared_ptr<DataStream> FileSystem::OpenFile(const Path &path, bool readOnly) {

        if (!Exists(path) || IsDirectory(path)) {
            Debug::LogError("Unable to find {}", path.toString());
            return nullptr;
        }

        uint8_t access = (readOnly) ? DataStream::ReadMode : DataStream::WriteMode;
        return Allocator::MakeShared<FileDataStream>(path, access);
    }

    bool FileSystem::IsFile(const Path &path) {
        return Exists(path) && !IsDirectory(path);
    }
}
