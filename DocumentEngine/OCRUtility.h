#pragma once

#include <memory>


namespace DocEngine::Core
{
	class ImageBlock;
	class OCRBlock;
}

namespace DocEngine::OCR
{
	class TesseractOCRProcessor;
	class OCRBlockBuilder;

	class OCRUtility
	{
	public:
		OCRUtility();

		bool BuildOCRBlockFromImage(
			const std::shared_ptr<Core::ImageBlock>& ImageBlock,
			std::shared_ptr<Core::OCRBlock>& OutOCRBlock);
		
	private:
		std::unique_ptr<TesseractOCRProcessor> OCRProcessor;
		std::unique_ptr<OCRBlockBuilder> BlockBuilder;
	};
}



