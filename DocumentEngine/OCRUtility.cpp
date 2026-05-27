#include "OCRUtility.h"

#include "ImageBlock.h"
#include "OCRBlock.h"

#include "TesseractOCRProcessor.h"
#include "OCRBlockBuilder.h"

namespace DocEngine::OCR
{
	OCRUtility::OCRUtility()
	{
		OCRProcessor = std::make_unique<TesseractOCRProcessor>();
		BlockBuilder = std::make_unique<OCRBlockBuilder>(OCRProcessor.get());
	}
	bool OCRUtility::BuildOCRBlockFromImage(const std::shared_ptr<Core::ImageBlock>& ImageBlock, std::shared_ptr<Core::OCRBlock>& OutOCRBlock)
	{
		if (!BlockBuilder || !ImageBlock)
			return false;

		OutOCRBlock = BlockBuilder->BuildFromImageBlock(ImageBlock);
		return OutOCRBlock != nullptr;
	}
}