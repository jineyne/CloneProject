#include "DataStream.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
    DataStream::DataStream(uint8_t access) : mAccess(access) {}

    DataStream::DataStream(String name, uint8_t access) : mName(name), mAccess(access) {}

    FileDataStream::FileDataStream(const Path &path, uint8_t accessMode, bool freeOnClose)
            : DataStream(accessMode), mPath(path), mFreeOnClose(freeOnClose) {
        std::ios::openmode mode = std::ios::binary;

        if ((accessMode & ReadMode) != 0) {
            mode |= std::ios::in;
        }

        if ((accessMode & WriteMode) != 0) {
            mode |= std::ios::out;
            mFStream = std::make_shared<std::fstream>();
            mFStream->open(path.toString().c_str(), mode);
            mIStream = mFStream;
        } else {
            mIfStream = std::make_shared<std::ifstream>();
            mIfStream->open(path.toString().c_str(), mode);
            mIStream = mIfStream;
        }

        if (mIStream->fail()) {
            Debug::LogWarning("Unable to open file {}", path.toString());
            return;
        }

        mIStream->seekg(0, std::ios_base::end);
        mSize = (size_t) mIStream->tellg();
        mIStream->seekg(0, std::ios_base::beg);
    }

    FileDataStream::~FileDataStream() {
        close();
    }

    size_t FileDataStream::read(void *buf, std::size_t num) {
        mIStream->read(static_cast<char *>(buf),
                       static_cast<std::streamsize>(num));

        return (size_t) mIStream->gcount();
    }

    size_t FileDataStream::write(const void *buf, size_t num) {
        size_t written = 0;

        if (isWritable() && mIStream) {
            mFStream->write(static_cast<const char *>(buf),
                            static_cast<std::streamsize>(num));
            written = num;
        }

        return written;
    }

    bool FileDataStream::eof() {
        return mIStream->eof();
    }

    void FileDataStream::close() {
        if (mIStream) {
            if (mIfStream) {
                mIfStream->close();
            }

            if (mFStream) {
                mFStream->flush();
                mFStream->close();
            }

            if (mFreeOnClose) {
                mIStream = nullptr;
                mIfStream = nullptr;
                mFStream = nullptr;
            }
        }
    }
}

