#include "PDFPageProcessor.h"

#include "DocumentPage.h"
#include "DocumentBlock.h"

#include "PDFPageRenderer.h"
#include "IOCRProcessor.h"

#include <fpdf_text.h>

namespace DocEngine::Parser
{
	PDFPageProcessor::PDFPageProcessor(Interface::IOCRProcessor* InOCRProcessor)
		: OCRProcessor(InOCRProcessor)
	{
	}
	Core::DocumentPage PDFPageProcessor::ProcessPage(FPDF_DOCUMENT Document, int PageIndex)
	{
        Core::DocumentPage Page;
        Page.PageIndex = PageIndex;

        FPDF_PAGE PdfPage = FPDF_LoadPage(Document, PageIndex);

        if (!PdfPage)
            return Page;

        // 1. TEXT BLOCKS
        auto TextBlocks = ExtractTextBlocks(PdfPage);
        for (auto& Block : TextBlocks)
        {
            Page.TextBlocks.push_back(Block);
        }

        // 2. OCR BLOCKS
        auto OCRBlocks = ExtractOCRBlocks(Document, PageIndex);
        for (auto& Block : OCRBlocks)
        {
            Page.OCRBlocks.push_back(Block);
        }

        FPDF_ClosePage(PdfPage);

        return Page;
	}
	std::vector<std::shared_ptr<Core::DocumentBlock>> PDFPageProcessor::ExtractTextBlocks(FPDF_PAGE Page)
	{
        std::vector<std::shared_ptr<Core::DocumentBlock>> Result;

        FPDF_TEXTPAGE TextPage = FPDFText_LoadPage(Page);

        if (!TextPage)
            return Result;

        int Count = FPDFText_CountChars(TextPage);

        std::string Text;
        Text.resize(Count);

        for (int i = 0; i < Count; i++)
        {
            wchar_t c = FPDFText_GetUnicode(TextPage, i);
            Text[i] = static_cast<char>(c);
        }

        auto Block = std::make_shared<Core::DocumentBlock>();
        Block->GetText() = Text;

        Result.push_back(Block);

        FPDFText_ClosePage(TextPage);

        return Result;
 	}
	std::vector<std::shared_ptr<Core::DocumentBlock>> PDFPageProcessor::ExtractOCRBlocks(FPDF_DOCUMENT Doc, int PageIndex)
	{
        std::vector<std::shared_ptr<Core::DocumentBlock>> Result;

        if (!OCRProcessor)
            return Result;

        PDFPageRenderer Renderer;

        std::string ImagePath = "page_" + std::to_string(PageIndex) + ".png";

       /* Renderer.RenderPageToImage(Doc, PageIndex, ImagePath);

        std::string OCRText;

        if (!OCRProcessor->ExtractTextFromImage(ImagePath, OCRText))
            return Result;

        if (!OCRText.empty())
        {
            auto Block = std::make_shared<Core::DocumentBlock>();
            Block->GetText() = OCRText;

            Result.push_back(Block);
        }*/

        return Result;
 	}
}