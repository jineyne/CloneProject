#pragma once

#include "cpf.hpp"

#include "RenderAPI/Buffer.hpp"

namespace cpf {
    class DLL_EXPORT GpuBuffer : public Buffer {
    private:
        GLuint mBufferId = 0;       //< 버퍼의 아이디입니다.
        GLenum mBufferType = 0;     //< 버퍼의 종류입니다.

        bool mIsZeroLock = false;   //<

    public:
        /**
         * 주어진 정보를 가지고 버퍼를 생성합니다.
         * @param bufferType 버퍼의 종류입니다.
         * @param size 요소의 크기입니다.
         * @param count 요소의 갯수입니다.
         * @param usage 버퍼 데이터를 관리하는 방법입니다.
         */
        GpuBuffer(GLenum bufferType, uint32_t size, BufferUsage usage);

        /**
         * 버퍼를 해제시킵니다.
         */
        ~GpuBuffer() override;

    public:
        // 주어진 버퍼 사용 방식을 GLenum으로 변경시킵니다.
        static GLenum GetUsage(BufferUsage usage);

    public:
        /**
         * 해당 버퍼의 gpu상의 메모리를 일반 메모리에 할당합니다.
         */
        void *map(uint32_t offset, uint32_t lenth) override;

        /**
         * 매핑한 데이터를 해제합니다.
         */
        void unmap() override;

        GLuint getBufferId() const override;
    };
}
