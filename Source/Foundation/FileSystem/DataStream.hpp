#pragma once

#include "cpf.hpp"
#include "FileSystem/Path.hpp"

namespace cpf {
    class DLL_EXPORT DataStream {
    public:
        enum {
            NoneMode = 1 << 0,
            ReadMode = 1 << 1,
            WriteMode = 1 << 2
        };

        String mName;

        size_t mSize = 0;

        uint8_t mAccess;

    public:
        DataStream(uint8_t access);

        DataStream(String name, uint8_t access);

        virtual ~DataStream() = default;

        uint8_t getAccessMode() const { return mAccess; }

        virtual bool isReadable() const { return mAccess & ReadMode; }

        virtual bool isWritable() const { return mAccess & WriteMode; }

        virtual size_t read(void *buf, size_t num) = 0;

        virtual size_t write(const void *buf, size_t num) = 0;

        virtual size_t size() const { return mSize; }

        virtual bool eof() = 0;

        virtual void close() = 0;
    };

    class DLL_EXPORT FileDataStream : public DataStream {
    protected:
        Path mPath;

        std::shared_ptr<std::istream> mIStream;

        std::shared_ptr<std::ifstream> mIfStream;

        std::shared_ptr<std::fstream> mFStream;

        bool mFreeOnClose;

    public:
        FileDataStream(const Path &path, uint8_t accessMode = ReadMode,
                       bool freeOnClose = true);

        ~FileDataStream() override;

        virtual size_t read(void *buf, std::size_t num) override;

        virtual size_t write(const void *buf, size_t num) override;

        virtual bool eof() override;

        virtual void close() override;
    };
}

