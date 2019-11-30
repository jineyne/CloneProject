#pragma once

#include "cpf.hpp"

#include "FileSystem/DataStream.hpp"
#include "FileSystem/Path.hpp"

namespace cpf {
    class DLL_EXPORT FileSystem {
    public:
        static std::shared_ptr<DataStream> OpenFile(const Path &path, bool readOnly = true);

        static std::shared_ptr<DataStream> CreateAndOpenFile(const Path &path);

        static bool Exists(const Path &path);

        static bool IsFile(const Path &path);

        static bool IsDirectory(const Path &path);

        static Path GetWorkingDirectoryPath();

        static Path GetTempDirectoryPath();
    };
}
