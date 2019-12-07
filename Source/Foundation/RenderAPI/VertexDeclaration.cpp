#include "VertexDeclaration.hpp"

#include "Debug/Debug.hpp"

namespace cpf {
     VertexElement::VertexElement(uint32_t offset, VertexElementType type, VertexElementSemantic semantic,
                                 uint32_t index, uint32_t instanceStepRate)
            : mOffset(offset), mType(type), mSemantic(semantic), mIndex(index), mInstanceStepRate(instanceStepRate) {}

    uint32_t VertexElement::GetTypeSize(VertexElementType type) {
        switch (type) {
            case VertexElementType::Float1:
                return sizeof(float);

            case VertexElementType::Float2:
                return sizeof(float) * 2;

            case VertexElementType::Float3:
                return sizeof(float) * 3;

            case VertexElementType::Float4:
                return sizeof(float) * 4;

            default:
                break;
        }

        return 0;
    }

    uint32_t VertexElement::GetTypeCount(VertexElementType type) {
        switch (type) {
            case VertexElementType::Float1:
                return 1;

            case VertexElementType::Float2:
                return 2;

            case VertexElementType::Float3:
                return 3;

            case VertexElementType::Float4:
                return 4;

            default:
                break;
        }

        Debug::LogError("Given vertex element type is invalid type");
        return 0;
    }

    size_t VertexElement::GetHash(const VertexElement &element) {
        size_t hash = 0;

        CombineHash(hash, element.mType);
        CombineHash(hash, element.mIndex);
        CombineHash(hash, element.mOffset);
        CombineHash(hash, element.mSemantic);
        CombineHash(hash, element.mInstanceStepRate);

        return hash;
    }

    bool VertexElement::operator==(const VertexElement &rhs) const {
        return ((mType != rhs.mType) || (mSemantic != rhs.mSemantic) || (mOffset != rhs.mOffset) ||
                (mIndex != rhs.mIndex) || (mInstanceStepRate != rhs.mInstanceStepRate));
    }

    bool VertexElement::operator!=(const VertexElement &rhs) const {
        return !(*this == rhs);
    }

    uint32_t VertexElement::getSize() const {
        return GetTypeSize(mType);
    }

    void VertexDeclaration::initialize() {
        //
    }

    bool VertexDeclaration::isCompatible(const VertexDeclaration *shaderDeclare) {
        const std::vector<VertexElement> &shaderElems = shaderDeclare->getElements();
        const std::vector<VertexElement> &bufferElems = getElements();

        for (auto shaderIter = shaderElems.begin(); shaderIter != shaderElems.end(); ++shaderIter) {
            const VertexElement *foundElement = nullptr;
            for (auto bufferIter = bufferElems.begin(); bufferIter != bufferElems.end(); ++bufferIter) {
                if (shaderIter->getSemantic() == bufferIter->getSemantic()) {
                    foundElement = &(*bufferIter);
                    break;
                }
            }

            if (foundElement == nullptr) {
                return false;
            }
        }

        return true;
    }

    std::vector<VertexElement> VertexDeclaration::getMissingElements(const VertexDeclaration *shaderDecl) {
        std::vector<VertexElement> missingElements;

        const std::vector<VertexElement> &shaderElems = shaderDecl->getElements();
        const std::vector<VertexElement> &bufferElems = getElements();

        for (auto shaderIter = shaderElems.begin(); shaderIter != shaderElems.end(); ++shaderIter) {
            const VertexElement *foundElement = nullptr;
            for (auto bufferIter = bufferElems.begin(); bufferIter != bufferElems.end(); ++bufferIter) {
                if (shaderIter->getSemantic() == bufferIter->getSemantic()) {
                    foundElement = &(*bufferIter);
                    break;
                }
            }

            if (foundElement == nullptr)
                missingElements.push_back(*shaderIter);
        }

        return missingElements;
    }

    const VertexElement *VertexDeclaration::getElement(uint32_t index) const {
        assert(index < mElementList.size());

        auto it = mElementList.begin();
        for (uint32_t i = 0; i < index; i++) {
            it++;
        }

        return reinterpret_cast<const VertexElement *>(&(*it));
    }

    const VertexElement *VertexDeclaration::findElementBySemantic(VertexElementSemantic semantic) const {
        for (auto &element : mElementList) {
            if (element.getSemantic() == semantic) {
                return reinterpret_cast<const VertexElement *>(&element);
            }
        }

        return nullptr;
    }

    VertexDeclaration::VertexDeclaration(const std::vector<VertexElement> &elements) {
        for (auto &elem : elements) {
            VertexElementType type = elem.getType();

            mElementList.push_back(VertexElement(elem.getOffset(), type, elem.getSemantic(), elem.getSemanticIdx(),
                                                 elem.getInstanceStepRate()));
        }
    }
}
