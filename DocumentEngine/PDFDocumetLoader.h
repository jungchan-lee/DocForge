#pragma once

#include <string>

#include <fpdfview.h>
#include <fpdf_text.h>

namespace DocEngine::Parser
{
	class PDFDocumetLoader
	{
    public:
        PDFDocumetLoader();
		~PDFDocumetLoader();

    public:
        bool LoadDocument(const std::string& FilePath);

        //void UnloadDocument();

        int GetPageCount() const;

        FPDF_PAGE LoadPage(int PageIndex);

        void ClosePage(FPDF_PAGE Page);

		FPDF_DOCUMENT GetDocument() const { return Document; }

    private:

        FPDF_DOCUMENT Document = nullptr;
	};
}



