#pragma once

#include <string>
#include <fpdfview.h>

namespace DocEngine::Interface
{
	class IOCRProcessor
	{
	public:
		virtual ~IOCRProcessor() = default;

	public:
		virtual bool ExtractTextFromBitmap(FPDF_BITMAP Image, std::string& OutText) = 0;

		virtual bool ExtractTextFromImage(const std::string& ImagePath, std::string& OutText) = 0;

	};
}