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

        // OCR 처리 후 저장되는 Text 변수
        std::string OCRText;

		// OCR 프로세서를 사용하여 이미지에서 텍스트 추출
        bool bSuccess = OCRProcessor->ExtractTextFromImage(ImageBlock->ImagePath, OCRText);

        if (!bSuccess)
        {
            return nullptr;
        }

		// OCR 결과를 기반으로 OCRBlock 생성
        auto Block = std::make_shared<Core::OCRBlock>();

        Block->PageIndex = ImageBlock->PageIndex;

        Block->Text = OCRText;

        Block->Bounds = ImageBlock->Bounds;

        return Block;
    }
}