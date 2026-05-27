#include "PDFPageParser.h"

#include "PDFTextExtractor.h"

#include "TextBlock.h"


namespace DocEngine::Parser
{
	Core::DocumentPage DocEngine::Parser::PDFPageParser::ParsePage(FPDF_PAGE Page, int PageIndex)
	{
        Core::DocumentPage ResultPage;

        ResultPage.PageIndex = PageIndex;

        PDFTextExtractor TextExtractor;

        std::string Text = TextExtractor.ExtractText(Page);

        auto TextBlock =  std::make_shared<Core::TextBlock>();

        TextBlock->PageIndex = PageIndex;
        TextBlock->Text = Text;

        ResultPage.TextBlocks.push_back(TextBlock);

        return ResultPage;
	}
}

