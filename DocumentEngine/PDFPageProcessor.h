#pragma once
#include <fpdfview.h>
#include <vector>
#include <memory>


namespace DocEngine::Core
{
	class DocumentPage;
	class DocumentBlock;
}

namespace DocEngine::Interface
{
	class IOCRProcessor;
}

namespace DocEngine::Parser
{

	class PDFPageProcessor
	{
	public:
		PDFPageProcessor(Interface::IOCRProcessor* InOCRProcessor);

		Core::DocumentPage ProcessPage(FPDF_DOCUMENT Document, int PageIndex);

	private:
		std::vector<std::shared_ptr<Core::DocumentBlock>> ExtractTextBlocks(FPDF_PAGE Page);
		std::vector<std::shared_ptr<Core::DocumentBlock>> ExtractOCRBlocks(FPDF_DOCUMENT Doc, int PageIndex);
	
	private:
		Interface::IOCRProcessor* OCRProcessor = nullptr;
	};

}

