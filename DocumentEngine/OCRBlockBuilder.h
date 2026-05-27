#pragma once

#include <memory>

namespace DocEngine::Core
{
	class ImageBlock;
	class OCRBlock;
}

namespace DocEngine::Interface
{
	class IOCRProcessor;
}

namespace DocEngine::OCR
{
	class OCRBlockBuilder
	{
    public:
        OCRBlockBuilder(Interface::IOCRProcessor* InOCRProcessor);

    public:
        std::shared_ptr<Core::OCRBlock>
            BuildFromImageBlock(const std::shared_ptr<Core::ImageBlock>& ImageBlock);

    private:
        Interface::IOCRProcessor* OCRProcessor = nullptr;
	};
}
