#include "ImageParser.h"

#include "Document.h"
#include "DocumentType.h"
#include "ImageBlock.h"

#include "OCRBlock.h"

#include "OCRBlockBuilder.h"
#include "TesseractOCRProcessor.h"


namespace DocEngine::Parser
{
	bool ImageParser::ParseDocument(const std::string& FilePath, Core::Document& Document)
	{
		// -----------------------------
		// ImageBlock 持失
		// -----------------------------

		auto ImageBlock = std::make_shared<Core::ImageBlock>();

		ImageBlock->ImagePath = FilePath;

		ImageBlock->PageIndex = 0;

		// -----------------------------
		// OCR Processor 持失
		// -----------------------------

		OCR::TesseractOCRProcessor OCRProcessor;

		// -----------------------------
		// OCRBlockBuilder 持失
		// -----------------------------

		OCR::OCRBlockBuilder Builder(&OCRProcessor);

		// -----------------------------
		// OCRBlock 持失
		// -----------------------------

		auto OCRBlock = Builder.BuildFromImageBlock(ImageBlock);

		if (!OCRBlock)
		{
			return false;
		}

		// -----------------------------
		// Page 持失
		// -----------------------------

		Core::DocumentPage Page;

		Page.PageIndex = 0;

		Page.OCRBlocks.push_back(OCRBlock);

		// -----------------------------
		// Document 煽舌
		// -----------------------------

		Document.Pages.push_back(Page);

		return true;
	}
}