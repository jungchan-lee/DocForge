#pragma once

#include "DocumentPage.h"

#include <fpdfview.h>
#include <fpdf_text.h>

namespace DocEngine::Parser
{
	class PDFPageParser
	{
	public:

		Core::DocumentPage ParsePage(FPDF_PAGE Page, int PageIndex);
	};
}



