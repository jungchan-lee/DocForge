#pragma once

#include <string>
#include <fpdfview.h>
#include <fpdf_text.h>

namespace DocEngine::Parser
{
	class PDFTextExtractor
	{
	public:
		//텍스트만 담당
		std::string ExtractText(FPDF_PAGE Page);
	};
}



