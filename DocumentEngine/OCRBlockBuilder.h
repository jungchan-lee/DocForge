#pragma once

#include <memory>
#include <fpdfview.h>

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
		// 일반 이미지 파일용
		std::shared_ptr<Core::OCRBlock>
			BuildFromImageBlock(const std::shared_ptr<Core::ImageBlock>& ImageBlock);
		
		// PDF bitmap용
		std::shared_ptr<Core::OCRBlock> BuildFromBitmap(
			FPDF_BITMAP Bitmap,
			const std::shared_ptr<Core::ImageBlock>& ImageBlock);
    private:
        Interface::IOCRProcessor* OCRProcessor = nullptr;
	};
}
