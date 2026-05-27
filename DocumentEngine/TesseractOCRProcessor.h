#pragma once

#include "IOCRProcessor.h"

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

#include <string>

namespace DocEngine::OCR
{
	class TesseractOCRProcessor : public Interface::IOCRProcessor
	{
	public:
		TesseractOCRProcessor();
		
		virtual ~TesseractOCRProcessor();

		virtual bool ExtractTextFromImage(
			const std::string& ImagePath,
			std::string& OutText) override;

	private:
		tesseract::TessBaseAPI TessAPI;
	};
}


