#pragma once

#include "IOCRProcessor.h"

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fpdfview.h>

#include <string>

namespace DocEngine::OCR
{
	class TesseractOCRProcessor : public Interface::IOCRProcessor
	{
	public:
		TesseractOCRProcessor();
		
		virtual ~TesseractOCRProcessor();

		virtual bool ExtractTextFromBitmap(
			FPDF_BITMAP Image,
			std::string& OutText) override;

		// 파일 기반 OCR
		bool ExtractTextFromImage(
			const std::string& ImagePath,
			std::string& OutText) override;

	private:
		tesseract::TessBaseAPI TessAPI;
	};
}


