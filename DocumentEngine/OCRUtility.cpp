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
	bool OCRUtility::BuildOCRBlockFromImage(FPDF_BITMAP Bitmap, const std::shared_ptr<Core::ImageBlock>& ImageBlock, std::shared_ptr<Core::OCRBlock>& OutOCRBlock)
	{
        if (!BlockBuilder)
        {
            return false;
        }

        if (!Bitmap)
        {
            return false;
        }

        if (!ImageBlock)
        {
            return false;
        }

        OutOCRBlock = BlockBuilder->BuildFromBitmap(Bitmap, ImageBlock);

        return OutOCRBlock != nullptr;
	}
    bool OCRUtility::BuildOCRBlockFromBitmap(FPDF_BITMAP Bitmap, const std::shared_ptr<Core::ImageBlock>& ImageBlock, std::shared_ptr<Core::OCRBlock>& OutOCRBlock)
    {
        if (!BlockBuilder)
        {
            return false;
        }

        OutOCRBlock =
            BlockBuilder->BuildFromBitmap(
                Bitmap,
                ImageBlock);

        return OutOCRBlock != nullptr;
    }
}