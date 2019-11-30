#include "Win32.hpp"

#include "FileSystem/FileSystem.hpp"
#include "Debug/Debug.hpp"

namespace cpf {
    static void Win32_handleError(DWORD error, const Path &path) {
        StringStream ss;
        switch (error) {
            case ERROR_FILE_NOT_FOUND:
            case ERROR_PATH_NOT_FOUND:
            case ERROR_BAD_NETPATH:
            case ERROR_CANT_RESOLVE_FILENAME:
            case ERROR_INVALID_DRIVE:
                Debug::LogError("Unable to find file at {}", path.toString());
                break;
            case ERROR_ACCESS_DENIED:
                Debug::LogError("Access denied at {}", path.toString());
                break;
            case ERROR_ALREADY_EXISTS:
            case ERROR_FILE_EXISTS:
                Debug::LogError("Already exist file or directory at {}", path.toString());
                break;
            case ERROR_INVALID_NAME:
            case ERROR_DIRECTORY:
            case ERROR_FILENAME_EXCED_RANGE:
            case ERROR_BAD_PATHNAME:
                Debug::LogError("Invalid path {}", path.toString());
                break;
            case ERROR_FILE_READ_ONLY:
                Debug::LogError("{} is read only", path.toString());
                break;
            case ERROR_CANNOT_MAKE:
                Debug::LogError("Unable to make file or directory at {}", path.toString());
                break;
            case ERROR_DIR_NOT_EMPTY:
                Debug::LogError("Not empty at {}", path.toString());
                break;
            case ERROR_WRITE_FAULT:
                Debug::LogError("Excepted during write file at {}", path.toString());
                break;
            case ERROR_READ_FAULT:
                Debug::LogError("Excepted during read file at {}", path.toString());
                break;
            case ERROR_SHARING_VIOLATION:
                Debug::LogError("Sharing violation at {}", path.toString());
                break;
            case ERROR_LOCK_VIOLATION:
                Debug::LogError("Lock violation at {}", path.toString());
                break;
            case ERROR_HANDLE_EOF:
                Debug::LogError("EOF reached for file at {}", path.toString());
                break;
            case ERROR_HANDLE_DISK_FULL:
            case ERROR_DISK_FULL:
                Debug::LogError("Disk full at {}", path.toString());
                break;
            case ERROR_NEGATIVE_SEEK:
                Debug::LogError("Negative seek at {}", path.toString());
                break;
            default:
                Debug::LogError("Undefined except ({}) at ", (uint32_t) error, path.toString());
                break;
        }
    }

    std::shared_ptr<DataStream> FileSystem::CreateAndOpenFile(const Path &path) {
        return Allocator::MakeShared<FileDataStream>(path, DataStream::WriteMode, true);
    }

    bool FileSystem::Exists(const Path &path) {
        DWORD attr = GetFileAttributes(path.toString().c_str());
        if (attr == 0xffffffff) {
            switch (GetLastError()) {
                case ERROR_FILE_NOT_FOUND:
                case ERROR_PATH_NOT_FOUND:
                case ERROR_NOT_READY:
                case ERROR_INVALID_DRIVE:
                    return false;
                default:
                    Win32_handleError(GetLastError(), path);
            }
        }
        return true;
    }

    bool FileSystem::IsDirectory(const Path &path) {
        DWORD attr = GetFileAttributes(path.toString().c_str());
        if (attr == 0xffffffff)
            Win32_handleError(GetLastError(), path);

        return (attr & FILE_ATTRIBUTE_DIRECTORY) != FALSE;
    }

    Path FileSystem::GetWorkingDirectoryPath() {
        DWORD len = GetCurrentDirectory(0, nullptr);
        if (len > 0) {
            auto *buf = static_cast<char *>(Allocator::Alloc<char>(len));
            DWORD n = GetCurrentDirectory(len, buf);
            if (n > 0 && n <= len) {
                StringStream ss;
                ss << buf;
                if (buf[len - 1] != '\\') {
                    ss << "\\";
                }

                Allocator::Free(buf);
                return ss.str();
            }

            Allocator::Free(buf);
        }

        return Path("");
    }

    Path FileSystem::GetTempDirectoryPath() {
        DWORD len = GetTempPath(0, nullptr);
        if (len > 0) {
            auto *buf = static_cast<char *>(Allocator::Alloc<char>(len));
            DWORD n = GetTempPath(len, buf);
            if (n > 0 && n <= len) {
                StringStream ss;
                ss << buf;
                if (buf[len - 1] != '\\') {
                    ss << "\\";
                }

                Allocator::Free(buf);
                return ss.str();
            }

            Allocator::Free(buf);
        }

        return Path("");
    }
}

