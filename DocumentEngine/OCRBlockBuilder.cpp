#include "OCRBlockBuilder.h"

#include "ImageBlock.h"
#include "OCRBlock.h"
#include "IOCRProcessor.h"

namespace DocEngine::OCR
{
	OCRBlockBuilder::OCRBlockBuilder(Interface::IOCRProcessor* InOCRProcessor)
		: OCRProcessor(InOCRProcessor)
	{
	}

	std::shared_ptr<Core::OCRBlock> OCRBlockBuilder::BuildFromImageBlock(const std::shared_ptr<Core::ImageBlock>& ImageBlock)
	{
		if (!OCRProcessor)
		{
			return nullptr;
		}

		if (!ImageBlock)
		{
			return nullptr;
		}

		std::string OCRText;

		bool bSuccess = OCRProcessor->ExtractTextFromImage(ImageBlock->ImagePath, OCRText);

		if (!bSuccess)
		{
			return nullptr;
		}

		if (OCRText.empty())
		{
			return nullptr;
		}

		auto Block = std::make_shared<Core::OCRBlock>();

		Block->PageIndex = ImageBlock->PageIndex;

		Block->Text = OCRText;

		return Block;
	}

	std::shared_ptr<Core::OCRBlock> OCRBlockBuilder::BuildFromBitmap(FPDF_BITMAP Bitmap, const std::shared_ptr<Core::ImageBlock>& ImageBlock)
    {
		if (!OCRProcessor)
		{
			return nullptr;
		}

		if (!ImageBlock)
		{
			return nullptr;
		}

		if (!Bitmap)
		{
			return nullptr;
		}

		std::string OCRText;

		bool bSuccess = OCRProcessor->ExtractTextFromBitmap(Bitmap, OCRText);

		if (!bSuccess)
		{
			return nullptr;
		}

		if (OCRText.empty())
		{
			return nullptr;
		}

		auto Block = std::make_shared<Core::OCRBlock>();

		Block->PageIndex = ImageBlock->PageIndex;

		Block->Text = OCRText;

		Block->Bounds = ImageBlock->Bounds;

		return Block;
    }
}