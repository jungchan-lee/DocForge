#include "PDFTextExtractor.h"
#include "PDFEncoding.h"



#include <vector>
namespace DocEngine::Parser
{
	std::string PDFTextExtractor::ExtractText(FPDF_PAGE Page)
	{
        FPDF_TEXTPAGE TextPage =  FPDFText_LoadPage(Page);

        int CharCount = FPDFText_CountChars(TextPage);

        std::vector<unsigned short> Buffer;

        Buffer.resize(CharCount + 1);

        FPDFText_GetText(
            TextPage,
            0,
            CharCount + 1,
            Buffer.data());

        std::wstring WideText(reinterpret_cast<wchar_t*>(Buffer.data()), CharCount);

        std::string Text = PDFEncoding::WideToUTF8(WideText);

        FPDFText_ClosePage(TextPage);

        return Text;
	}
}