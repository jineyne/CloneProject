#pragma once

#include "cpf.hpp"

namespace cpf {
    /**
     * 버퍼 데이터를 어떻게 관리할지 지정하는 열거형입니다.
     */
    enum class BufferUsage {
        Static = 1,
        Dynamic,
        Stream,
        Default = Static,
    };

    class DLL_EXPORT Buffer {
    protected:
        uint32_t mSize = 0;                         //< 버퍼의 크기입니다.
        BufferUsage mUsage = BufferUsage::Default;  //< 버퍼 데이터를 어떻게 관리하는지 저장합니다.

        uint32_t mElementSize = 0;                  //< 요소의 크기입니다.
        uint32_t mElementCount = 0;                 //< 요소의 갯수입니다
        bool mIsLocked = false;                     //< 버퍼가 잠겨있는지의 여부입니다.
    
    public:
        Buffer(uint32_t size, uint32_t count, BufferUsage usage);
        virtual ~Buffer() = default;

    public:
        virtual void *map(uint32_t offset, uint32_t length) = 0;
        virtual void unmap() = 0;

        uint32_t getSize() const { return mElementSize; }
        uint32_t getCount() const { return mElementCount; }
        virtual GLuint getBufferId() const = 0;
    };
}
